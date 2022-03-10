#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H_
namespace sdds {
	class Status{	
		char* m_description{};
		int m_statusCode{};
	public:
		Status(const char * desc= nullptr);
		Status(const Status& srcVarible);
		Status& operator = (const Status& srcVarible);
		Status& operator = (const int srcValue);
		// student defined overloading to make the process easier // 
		Status& operator= (const char* srcStr);
		~Status();
		operator int()const;
		operator const char* ()const;
		operator bool() const;
		Status& clear();
	};
	std::ostream& operator << (std::ostream& ostr, const Status& source);

}
#endif // !SDDS_STATUS_H
