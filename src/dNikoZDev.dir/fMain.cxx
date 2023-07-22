#ifndef dNikoZDevMainCxx
#define dNikoZDevMainCxx
#include <dNikoZDev.dir/fHead.hxx>
//content
#ifdef dNikoZDevMakeExe
//actions
int main(int vArgC, char *vArgV[])
{
#ifdef dNikoZDevTestExe
	if constexpr(1)
	{
		std::cout << "hello test" << std::endl;
	}
#endif//dNikoZDevTestExe
	return nNikoZDev::fMain(vArgC, vArgV);
}//main
#endif//dNikoZDevMakeExe
#endif//dNikoZDevMainCxx
