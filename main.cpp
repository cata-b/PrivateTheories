#include "GUI.h"
#include "UI.h"
#include <QtWidgets/QApplication>
#include <QSettings>

#include "StandardClearanceTableModel.h"

#include "SetDebugNew.h"
#include "ReportingHook.h"
#include "KeyboardShortcutFilter.h"
using namespace std;

QString get_file_extension(const QString& file_name)
{
	auto dot_position = file_name.lastIndexOf('.');
	if (dot_position < file_name.length())
		return file_name.mid(dot_position + 1);
	return "";
}

int main(int argc, char* argv[])
{
#if defined(WIN32) && defined(_DEBUG)
	setFilterDebugHook();
#endif

	int return_value = 0;
	{
		QSettings program_settings{"settings.ini", QSettings::IniFormat};
		QString repository_type, user_repository_type, file_location, database_connection_string, mylist_location,
		        UI_type;

		Repository *main_repository, *user_repository;

		repository_type = program_settings.value("repository").toString();
		if (repository_type == "file")
		{
			file_location = program_settings.value("file_location").toString();
			if (file_location == "")
			{
				qFatal("Empty file location for main repository.");
				return 0;
			}
			try
			{
				main_repository = get_file_extension(file_location) == "html"
					                  ? static_cast<Repository*>(new HTMLRepository(file_location.toStdString()))
					                  : new FileRepository(file_location.toStdString());
			}
			catch (exception& e)
			{
				qFatal(e.what());
				return 0;
			}
		}
		else if (repository_type == "db")
		{
			database_connection_string = program_settings.value("database_connection_string").toString();
			if (database_connection_string == "")
			{
				qFatal("Empty connection string for main repository.");
				return 0;
			}
			try
			{
				main_repository = static_cast<Repository*>(new DatabaseRepository(
					database_connection_string.toStdString()));
			}
			catch (exception& e)
			{
				qFatal(e.what());
				return 0;
			}
		}
		else if (repository_type == "inmemory")
			main_repository = static_cast<Repository*>(new InMemoryRepository());
		else
		{
			qFatal(("Invalid main repository type: " + repository_type).toStdString().c_str());
			return 0;
		}

		user_repository_type = program_settings.value("user_repository").toString();
		if (user_repository_type == "file")
		{
			mylist_location = program_settings.value("my_list_location").toString();
			if (mylist_location == "")
			{
				qFatal("Empty file location for user repository.");
				return 0;
			}
			try
			{
				user_repository = get_file_extension(mylist_location) == "html"
					                  ? static_cast<Repository*>(new HTMLRepository(mylist_location.toStdString()))
					                  : new FileRepository(mylist_location.toStdString());
			}
			catch (exception& e)
			{
				qFatal(e.what());
				return 0;
			}
		}
		else if (user_repository_type == "inmemory")
			user_repository = static_cast<Repository*>(new InMemoryRepository());
		else
		{
			qFatal(("Invalid user repository type: " + user_repository_type).toStdString().c_str());
			return 0;
		}

		vector<unique_ptr<Action>> &Undo = *new vector<unique_ptr<Action>>, &Redo = *new vector<unique_ptr<Action>>;
		StandardClearanceController* standard_controller = new StandardClearanceController(
			main_repository, user_repository, Undo, Redo);
		SeniorClearanceController* senior_controller = new SeniorClearanceController(main_repository, Undo, Redo);
		StandardClearanceTableModel standard_window_table_model(*user_repository);
		QApplication application(argc, argv);
		KeyboardShortcutFilter filter{&application, senior_controller, &application};
		GUI gui{senior_controller, standard_controller, standard_window_table_model};
		gui.installEventFilter(&filter);
		QObject::connect(&filter, &KeyboardShortcutFilter::undo, &gui, &GUI::undo_button_click);
		QObject::connect(&filter, &KeyboardShortcutFilter::redo, &gui, &GUI::redo_button_click);
		gui.show();
		return_value = application.exec();
	}
	_CrtDumpMemoryLeaks();
	return return_value;
}
