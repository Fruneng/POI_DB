#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>

typedef std::map<std::string, std::string> KeyValueMap;
typedef KeyValueMap::iterator KeyValueIt;
typedef std::map<std::string, boost::shared_ptr<KeyValueMap> > SectionMap;
typedef SectionMap::iterator SectionIt;

class IniFile
{
public:
	IniFile():IsCaseSensitive(false),ChEqual('='), ChComment('#'),Ignore("\f\n\t\r\v "),SectionLCh('['),SectionRCh(']')
	{

	};
	IniFile(bool IsKeyCase, unsigned char ChEqual_, unsigned char ChComment_, const char * const Ignore_, char LCh_, char RCh_)
		:IsCaseSensitive(IsKeyCase),ChEqual(ChEqual_),ChComment(ChComment_),Ignore(Ignore_),SectionLCh(LCh_),SectionRCh(RCh_)
	{

	};
	~IniFile()
	{

	};
	void SetCaseSensitive(bool IsCaseSensitive_)
	{
		IsCaseSensitive = IsCaseSensitive_;
	}
	bool GetCaseSensitive()
	{
		return IsCaseSensitive;
	}

	void SetChEqual(char ChEqual_)
	{
		ChEqual = ChEqual_;
	}
	char GetChEqual()
	{
		return ChEqual;
	}

	void SetIgnore(const char * Ignore_)
	{
		Ignore = Ignore_;
	}
	std::string GetIgnore()
	{
		return Ignore;
	}

	void SetSectionLCh(char SectionLCh_)
	{
		SectionLCh = SectionLCh_;
	}
	char GetSectionLCh()
	{
		return SectionLCh;
	}

	void SetSectionRCh(char SectionRCh_)
	{
		SectionRCh = SectionRCh_;
	}
	char GetSectionRCh()
	{
		return SectionRCh;
	}

	bool open(const std::string & IniFileName)
	{
		return do_open(IniFileName);
	};

	std::string read(std::string const & Section, std::string const & Key)
		//read a string by return it
	{
		std::string ret;
		std::string UpperSection(Section),UpperKey(Key);
		if (!IsCaseSensitive)
		{
			TransToUpper(UpperSection);
			TransToUpper(UpperKey);
		}
		SectionIt SecIt = Ini_Section.find(UpperSection);
		if (SecIt != Ini_Section.end())
		{
			KeyValueIt KeyIt = SecIt->second->find(UpperKey);
			if (KeyIt != SecIt->second->end())
			{
				ret = KeyIt->second;
			}
		}
		return ret;
	};

//	template<typename T>
//	bool read(std::string const & Section, std::string const & Key, T & Dst)
//		//read a typename T object through pass the third parameter by reference
//	{
//		try
//		{
//			Dst = boost::lexical_cast<T>(read(Section,Key));
//		}
//		catch(...) //boost::bad_lexical_cast
//		{
//			return false;
//		}
//		return true;
//	}
//
//	template<>
//	bool read(std::string const & Section, std::string const & Key, std::string & Dst)
//		//read a string through pass the third parameter by reference
//	{
//		Dst = read(Section,Key);
//		return !Dst.empty();
//	}

protected:
	void TransToUpper(std::string & Source)
	{
		for (std::string::iterator it = Source.begin(); it != Source.end(); ++it)
			*it = ::toupper(*it);
	}
	bool do_open(const std::string & IniFileName)
	{
		std::ifstream fReadIni(IniFileName.c_str());
		if(!fReadIni)
			return false;

#pragma region Initial
		boost::shared_ptr<KeyValueMap> KeyValueMapPtr;
		std::string Line,Section,Key,EqualSymbol,Value,Temp;
		std::string::size_type PosEqualSymbol,PosComment;
		std::string::size_type left,right;

		Section = "_UnNamedSection";
		KeyValueMapPtr.reset(new KeyValueMap);
		Ini_Section.clear();
		Ini_Section.insert(SectionMap::value_type(Section,KeyValueMapPtr));
#pragma endregion Initial

		while(!fReadIni.eof())
		{
			getline(fReadIni, Line);
			if(!Line.empty())
			{
				left = Line.find_first_not_of(Ignore.c_str());
				right = Line.find_last_not_of(Ignore.c_str());
#pragma region Section
				if (left != std::string::npos && right != std::string::npos && left < right && Line.at(left) == SectionLCh && Line.at(right) == SectionRCh)
				{
					Temp = Line.substr(left+1,right-left-1);
					right = Temp.find_last_not_of(Ignore.c_str());
					left = Temp.find_first_not_of(Ignore.c_str());
					if (left != std::string::npos && right != std::string::npos)
					{
						Section = Temp.substr(left,right-left+1);
						if (!IsCaseSensitive)
						{
							TransToUpper(Section);
						}
						SectionIt SecIt = Ini_Section.find(Section);
						if (SecIt != Ini_Section.end())
						{
							KeyValueMapPtr = SecIt->second;
						}
						else
						{
							KeyValueMapPtr.reset(new KeyValueMap);
							Ini_Section.insert(SectionMap::value_type(Section,KeyValueMapPtr));
						}
					}
				}
#pragma endregion Section
#pragma region Content
				else
				{
					PosEqualSymbol = Line.find_first_of(ChEqual);
					PosComment = Line.find_first_of(ChComment);
					if (PosEqualSymbol != std::string::npos && (PosComment == std::string::npos || PosEqualSymbol < PosComment))
					{
						Temp = Line.substr(0,PosEqualSymbol);
						left = Temp.find_first_not_of(Ignore.c_str());
						right = Temp.find_last_not_of(Ignore.c_str());
						if (left != std::string::npos && right != std::string::npos)
						{
							Key = Temp.substr(left,right-left+1);
							if (PosComment != std::string::npos)
							{
								Temp = Line.substr(PosEqualSymbol+1,PosComment-PosEqualSymbol-1);
							}
							else
							{
								Temp = Line.substr(PosEqualSymbol+1);
							}
							left = Temp.find_first_not_of(Ignore.c_str());
							right = Temp.find_last_not_of(Ignore.c_str());
							if (left != std::string::npos)
							{
								Value = Temp.substr(left,right-left+1);
								if (!IsCaseSensitive)
								{
									TransToUpper(Key);
								}
								KeyValueMapPtr->insert(KeyValueMap::value_type(Key,Value));
							}
						}
					}
				}
#pragma endregion Content
			}
		}
		return true;
	};
private:
	SectionMap  Ini_Section;
	bool IsCaseSensitive;
	unsigned char ChEqual, ChComment, SectionLCh, SectionRCh;
	std::string Ignore;
};
