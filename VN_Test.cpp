#include "VNEngine.hpp"

const char* img_path = "E:\\Development\\Projects\\VisualNovelEngine\\monica_3a.png";
const char* img_path1 = "E:\\Development\\Projects\\VisualNovelEngine\\1001621.png";

int main()
{
	VNGame game;
	VNWindow* window;
	int success = game.VNInit(&window, 1600, 900, "test", 0, 30);
	if (!success) return -1;
	VNShader* shader = new VNShader();
	game.VNSetShader(shader);
	//window->VNSetWindowSize(1300, 900);
	//window->VNSetWindowPos(0, 30);
	VNImage* imgtest = new VNImage(img_path1);
	game.VNSetVertex(imgtest, 0, 0);
	game.VNSetBackgroundColor(0.2f, 0.3f, 0.3f, 1.0f);

	game.VNRun();
	//system("pause");
	return 0;
}
