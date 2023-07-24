#ifndef dNikoZDevHeadHxx
#define dNikoZDevHeadHxx
//headers
#include <dLibAsist.dir/fHead.hxx>
#include <iostream>
//content
namespace nNikoZDev
{
namespace nMain
{
//actions
#ifdef dNikoZDevMakeExe
inline auto fMain(int vArgC, char *vArgV[])
{
#ifdef dNikoZDevTestExe
	fOlog("hello test");
#endif//dNikoZDevTestExe
	fOlog("hello world");
	return 0;
}//fMain
#endif//dNikoZDevMakeExe
}//namespace nMain
}//namespace nNikoZDev
#endif//dNikoZDevHeadHxx
