#ifndef dNikoZDevMainCxx
#define dNikoZDevMainCxx
#include <dNikoZDev.dir/fMain.hxx>
//content
#ifdef dNikoZDevMakeProjExe
//actions
int main(int vArgC, char *vArgV[])
{
#	ifdef dNikoZDevTestProjExe
	if constexpr(1)
	{
		std::cout << "hello test" << std::endl;
	}
#	endif//dNikoZDevTestProjExe
	return nNikoZDev::fMain(vArgC, vArgV);
}//main
#endif//dNikoZDevMakeProjExe
#endif//dNikoZDevMainCxx
