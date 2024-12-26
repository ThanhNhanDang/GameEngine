namespace VIEngine {
	struct ApplicationConfiguraion
	{
		int Width, Height;
		const char* Title;
	};


	class Application {
	public:
		virtual ~Application() = default;
		virtual bool Init() { return true; }
		void Run();
		virtual void Shutdown() {}
	protected:
		Application() = default;
		Application(const ApplicationConfiguraion&);
	private:
		ApplicationConfiguraion mConfig;
	};

	extern Application* CreateApplication();
}