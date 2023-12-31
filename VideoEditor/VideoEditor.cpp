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

		ImGui::Begin("Editor", NULL, ImGuiWindowFlags_MenuBar);

		videosHandle();
		parametersHandle();

		ImGui::End();

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
		auto end = std::chrono::system_clock::now();
		auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << elapsed << '\n';
	}
}

void VideoEditor::videosHandle() 
{
	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Sources")) //Window targetting menu
		{
			videoListCreate();
		}
		ImGui::EndMenuBar();
	}
	if (currentWindow_ != nullptr)
		ImGui::Text("Targetting: %s", currentWindow_->videoNameGet().c_str());

	ImGui::Checkbox("Open Video", &this->checkBox_);
	ImGui::SameLine();
	ImGui::InputText("Text", &this->bufferVidName_);
	if (this->checkBox_) 
	{
		for (auto& [winName, video] : this->videoWindows_)
			video->run();
	}
	if (ImGui::Button("Run video")) 
	{
		if (this->bufferVidName_.ends_with(".mp4") && std::filesystem::exists(this->bufferVidName_)) //mp4
		{
			this->videoWindowCreate(this->bufferVidName_.substr(0, this->bufferVidName_.length()), this->bufferVidName_);
			this->bufferVidName_.clear();
		}
		else if (isNumber(this->bufferVidName_)) //cam
		{
			this->videoWindowCreate("cam" + this->bufferVidName_, std::stoi(this->bufferVidName_));
			this->bufferVidName_.clear();
		}
		else if (this->bufferVidName_.starts_with("http") || this->bufferVidName_.starts_with("rtsp")) //ip cam
		{
			this->videoWindowCreate("cam" + this->bufferVidName_, this->bufferVidName_);
			this->bufferVidName_.clear();
		}

	}
}

void VideoEditor::parametersHandle() 
{
	if (ImGui::BeginMenuBar()) 
	{
		if (ImGui::BeginMenu("Parameters"))
		{
			parameterListCreate();
		}
		ImGui::EndMenuBar();
	}
}

void VideoEditor::parameterListCreate() 
{
	for (auto& [name, type] : Param::map) {
		if (this->currentWindow_ != nullptr && this->currentWindow_->videoGet()->parametersGet()->contains(type))
		{
			ImGui::Bullet();
			ImGui::SameLine();
		}
		if (ImGui::MenuItem(name.c_str())) //TODO: implement name to parameter initialization dependency
		{
			if(this->currentWindow_ != nullptr)
				this->currentWindow_->videoParameterCreate(std::shared_ptr<Parameter>(new Parameter{ type, cv::Size(11, 11) }));
		}
	}
	ImGui::EndMenu();
}

void VideoEditor::videoListCreate()
{
	for (auto& [name, video] : this->videoWindows_)
	{
		if (ImGui::MenuItem(name.c_str()))
		{
			this->currentWindow_ = this->videoWindows_[name];
		}
	}
	ImGui::EndMenu();
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
