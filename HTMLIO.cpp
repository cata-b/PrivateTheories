#include "HTMLIO.h"
#include <functional>

#include "SetDebugNew.h"
using namespace std;

istream& operator>>(istream& in, TagIn& tag)
{
	std::string open_tag;
	tag.name = "";
	tag.content = "";
	tag.attributes = "";
	if (getline(in, open_tag, '>'))
	{
		auto first_smaller_character = find_if(open_tag.begin(), open_tag.end(),
		                                       [](char character) { return !isspace(character); });
		if (first_smaller_character != open_tag.end())
		{
			open_tag = open_tag.substr(first_smaller_character - open_tag.begin());
			tag.name = open_tag.substr(1, open_tag.find_first_of(' ') - 1);
			open_tag.erase(0, tag.name.size() + 1);
			if (open_tag.length() != 0)
			{
				auto attributes_start = open_tag.find_first_not_of(' '), attributes_end = open_tag.find_last_of('>');
				tag.attributes = open_tag.substr(attributes_start, attributes_end - attributes_start);
				if (tag.name == "!DOCTYPE")
					return in;
			}
			std::string tag_content;
			std::string tag_chunk;
			getline(in, tag_chunk, '>');
			do
			{
				tag_content += tag_chunk + '>';
				auto last_slash = tag_chunk.find_last_of('/');
				if (tag_chunk.substr(last_slash + 1, tag_chunk.length() - last_slash) == tag.name)
				{
					tag.content = tag_content.substr(0, tag_content.find_last_of('<'));
					break;
				}
			}
			while (getline(in, tag_chunk, '>'));
		}
	}
	while (tag.content[0] == '\n') tag.content.erase(tag.content.begin());
	while (tag.content.length() != 0 && tag.content[tag.content.length() - 1] == '\n') tag
	                                                                                   .content.erase(
		                                                                                   tag.content.end() - 1);
	return in;
}
