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
	ImGui::Checkbox("Open Video", &checkBox_);
	ImGui::SameLine();
	ImGui::InputText("Text", &this->bufferVidName_);
	if (checkBox_) 
	{
		for (auto& [winName, video] : this->videoWindows_)
			video->run();
	}
	if (ImGui::Button("Run video")) 
	{
		if (this->bufferVidName_.ends_with(".mp4") && std::filesystem::exists(this->bufferVidName_))
		{
			this->videoWindowCreate(this->bufferVidName_.substr(0, this->bufferVidName_.length()), this->bufferVidName_);
			this->bufferVidName_.clear();
		}
		else if (isNumber(this->bufferVidName_)) 
		{
			this->videoWindowCreate("cam" + this->bufferVidName_, std::stoi(this->bufferVidName_));
			this->bufferVidName_.clear();
		}
	}
}

void VideoEditor::handleParameters(Video& v) {
	if (ImGui::BeginMenuBar()) 
	{
		if (ImGui::BeginMenu("Parameters"))
		{
			if (ImGui::MenuItem("Blur"))
			{

			}
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
