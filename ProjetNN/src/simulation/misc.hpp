#ifndef   	MISC_H
# define   	MISC_H


class Exception
{
public:
  Exception(const char* msg) : _msg(msg) {};
  Exception(const std::string& str) : _msg(str) {}
  const std::string& get_msg() const { return _msg; }
protected:
  std::string _msg;
};

template<typename T>
inline T normalize_angle(T a)
  {
     while (a > M_PI)
       a -= 2*M_PI;
     while (a < -M_PI)
       a += 2*M_PI;
     return a;
  }  
  
  template<typename T>
  inline T normalize_angle_2pi(T a)
  {
     while (a > 2 * M_PI)
       a -= 2 * M_PI;
     while (a < 0)
       a += 2 * M_PI;
     return a;
  }  



#endif	    /* !MISC_HH_ */
