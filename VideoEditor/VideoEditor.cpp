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

	for(;;) {
		auto start = std::chrono::system_clock::now();
		glfwPollEvents();
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		ImGui::Begin("Editor");

		handleVideos();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << elapsed << '\n';
	}
}

void VideoEditor::handleVideos() {
	//bool checkBox { false };
	//std::string textBuffer;
	ImGui::Checkbox("Open Video", &checkBox_);
	ImGui::InputText("Text", &textBuffer_);
	if (checkBox_) 
	{
		for (auto& [winName, video] : this->videoWindows_)
			video->run();
	}
	if (ImGui::Button("Run video")) 
	{
		if (textBuffer_.ends_with(".mp4")) 
		{
			this->videoWindowCreate(textBuffer_.substr(0, textBuffer_.length()), textBuffer_);
				textBuffer_.clear();
		}
		else if (isNumber(textBuffer_)) 
		{
			this->videoWindowCreate("cam" + textBuffer_, std::stoi(textBuffer_));
				textBuffer_.clear();
		}
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
