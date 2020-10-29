#pragma once
#include <stack>
#include <string>
#include <iostream>

class TagAttributes
{
private:
	std::string attributes;
public:
	TagAttributes(std::string Attributes) : attributes(Attributes)
	{
	};

	TagAttributes(const char* Attributes) : attributes(Attributes)
	{
	};
	std::string GetAttributes() const { return attributes; }
};

class TagOut
{
public:
	TagOut(std::string tag_name) : tag(tag_name)
	{
	};

	TagOut(const char* tag_name) : tag(tag_name)
	{
	};
private:
	std::string tag;

	class Tagger
	{
	private:
		std::string tag;
		std::ostream& out;
	public:
		Tagger(const TagOut& Tag, std::ostream& output) : tag(Tag.tag), out(output)
		{
		}

		template <typename NextType>
		std::ostream& operator<<(const NextType& next)
		{
			return out << "<" << tag << ">" << next;
		}

		template <>
		std::ostream& operator<<(const TagAttributes& next)
		{
			return out << '<' << tag << ' ' << next.GetAttributes() << '>';
		}
	};

	friend Tagger operator<<(std::ostream& out, const TagOut& tag_out)
	{
		return Tagger(tag_out, out);
	}
};

class TagIn
{
private:
	std::string name, attributes, content;
public:
	TagIn()
	{
	};
	std::string GetName() const { return name; };
	std::string GetAttributes() const { return attributes; };
	std::string GetContent() const { return content; };
	friend std::istream& operator>>(std::istream& in, TagIn& tag);
};
