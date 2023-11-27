#include "VideoEditor.h"

VideoEditor::VideoEditor()
{
	//this->controlPanelCreate(ControlPanel::defaultName);
}

VideoEditor::~VideoEditor()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
	glfwTerminate();
}

int VideoEditor::run() {
	if (!glfwInit())
		return -1;
	GLFWwindow* window = glfwCreateWindow(1920, 1080, "glfw window", glfwGetPrimaryMonitor(), nullptr);
	glfwSetWindowCloseCallback(window, [](GLFWwindow* window) { glfwSetWindowShouldClose(window, GL_FALSE); });
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gl3wInit();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	int input = 1;
	WindowVideo win1("Cam", 0);
	WindowVideo win2("Vid", "doanel.mp4");
	for(;;) {
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		win1.run();
		win2.run();
		
		//ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}
}

std::shared_ptr<WindowVideo> VideoEditor::getWindow(const std::string& name)
{
	return this->videoWindows_.find(name)->second;
}

void VideoEditor::videoWindowCreate(const std::string& name, int source)
{
	this->videoWindows_.try_emplace(name, new WindowVideo{ name, source });
}

void VideoEditor::videoWindowCreate(const std::string& name, const std::string& source)
{
	this->videoWindows_.try_emplace(name, new WindowVideo{ name, source });
}

void VideoEditor::videoWindowDestroy(const std::string& name)
{
	//this->windows_[name]->join();
	std::map<std::string, std::shared_ptr<WindowVideo>>::size_type erased = this->videoWindows_.erase(name);
	//std::cout << erased << '\n';
	//this->windows_.erase(name);
}

void VideoEditor::controlPanelCreate(const std::string& name)
{
	this->controlPanels_.try_emplace(name, new ControlPanel{ name });
}

void VideoEditor::controlPanelDestroy(const std::string& cpName)
{
	//this->controlPanels_.at(cpName)->join();
	std::map<std::string, std::shared_ptr<ControlPanel>>::size_type erased = this->controlPanels_.erase(cpName);
}

std::shared_ptr<WindowVideo> VideoEditor::operator[](const std::string& name)
{
	return this->videoWindows_.at(name);
}
