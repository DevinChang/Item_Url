#pragma once

	#using<System.Drawing.dll>
	#using<System.dll>
	#using<System.Windows.Forms.dll>

namespace WebBrowser {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Security::Permissions;

	/// <summary>
	/// Form1 摘要
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: 在此处添加构造函数代码
			//
		}

	protected:
		System::Windows::Forms::MainMenu ^main_menu;
		System::Windows::Forms::MenuItem ^menu_item_file;
		System::Windows::Forms::MenuItem ^menu_item_file_save;
		System::Windows::Forms::TextBox ^textbox_address;
		System::Windows::Forms::Panel ^panel;
		System::Windows::Forms::Button ^button_go;
		System::Windows::Forms::Button ^button_back;
		System::Windows::Forms::Button ^button_forward;
		System::Windows::Forms::Button ^button_refresh;
		System::Windows::Forms::Button ^button_home;
		System::Windows::Forms::Button ^button_stop;
		System::Windows::Forms::WebBrowser ^webbrowser;
		System::Windows::Forms::StatusBar ^status_bar;

		[SecurityPermission(SecurityAction::Demand, Flags=SecurityPermissionFlag::UnmanagedCode)]
		void InitializeComponent(void)
		{
			this->main_menu = gcnew System::Windows::Forms::MainMenu;
			this->menu_item_file = gcnew System::Windows::Forms::MenuItem;
			this->menu_item_file_save = gcnew System::Windows::Forms::MenuItem;
			this->textbox_address = gcnew System::Windows::Forms::TextBox;
			this->button_go = gcnew System::Windows::Forms::Button;
			this->button_back = gcnew System::Windows::Forms::Button;
			this->button_forward = gcnew System::Windows::Forms::Button;
			this->button_home = gcnew System::Windows::Forms::Button;
			this->button_refresh = gcnew System::Windows::Forms::Button;
			this->button_stop = gcnew System::Windows::Forms::Button;
			this->panel = gcnew System::Windows::Forms::Panel;
			this->webbrowser = gcnew System::Windows::Forms::WebBrowser;
			this->status_bar = gcnew System::Windows::Forms::StatusBar;

			//main_menu
			array<System::Windows::Forms::MenuItem ^> ^tmp0 = {this->menu_item_file};
			this->main_menu->MenuItems->AddRange(tmp0);

			//menu_item_file
			this->menu_item_file->Index = 0;
			array<System::Windows::Forms::MenuItem ^> ^tmp1 = {this->menu_item_file_save};
			this->menu_item_file->MenuItems->AddRange(tmp1);
			this->menu_item_file->Text = "菜单";

			//menu_item_file_save
			this->menu_item_file_save->Index = 0;
			this->menu_item_file_save->Text = "另存为";
			this->menu_item_file_save->Click += gcnew System::EventHandler(this, &Form1::menu_item_file_save_click);

			//textbox_address
			this->textbox_address->Location = System::Drawing::Point(100, 0);
			this->textbox_address->Size = System::Drawing::Size(360, 20);
			this->textbox_address->TabIndex = 1;
			this->textbox_address->Text = "";
			this->textbox_address->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, 
																			&Form1::textbox_address_keydown);

			//button_go
			this->button_go->Location = System::Drawing::Point(465, 0);
			this->button_go->Size = System::Drawing::Size(48,20);
			this->button_go->TabIndex = 2;
			this->button_go->Text = "Go";
			this->button_go->Click += gcnew System::EventHandler(this, &Form1::button_go_click);

			//button_refresh
			this->button_refresh->Location = System::Drawing::Point(518, 0);
			this->button_refresh->Size = System::Drawing::Size(48,20);
			this->button_refresh->TabIndex = 3;
			this->button_refresh->Text = "Fresh";
			this->button_refresh->Click += gcnew System::EventHandler(this, &Form1::button_refresh_click);

			//button_home
			this->button_home->Location = System::Drawing::Point(571, 0);
			this->button_home->Size = System::Drawing::Size(48,20);
			this->button_home->TabIndex = 4;
			this->button_home->Text = "Home";
			this->button_home->Click += gcnew System::EventHandler(this, &Form1::button_home_click);

			////button_forward
			this->button_forward->Location = System::Drawing::Point(50, 0);
			this->button_forward->Size = System::Drawing::Size(48,20);
			this->button_forward->TabIndex = 5;
			this->button_forward->Text = "Fward";
			this->button_forward->Click += gcnew System::EventHandler(this, &Form1::button_forward_click);

			//button_back
			this->button_back->Location = System::Drawing::Point(0, 0);
			this->button_back->Size = System::Drawing::Size(48,20);
			this->button_back->TabIndex = 6;
			this->button_back->Text = "Back";
			this->button_back->Click += gcnew System::EventHandler(this, &Form1::button_back_click);

			//panel
			this->panel->Controls->Add(this->textbox_address);
			this->panel->Controls->Add(this->button_go);
			this->panel->Controls->Add(this->button_refresh);
			this->panel->Controls->Add(this->button_home);
			this->panel->Controls->Add(this->button_back);
			this->panel->Controls->Add(this->button_forward);
			this->panel->Dock = System::Windows::Forms::DockStyle::Top;
			this->panel->Location = System::Drawing::Point(0, 0);
			this->panel->Size = System::Drawing::Size(624, 24);
			this->panel->TabIndex = 11;

			//webbrowser
			this->webbrowser->AllowWebBrowserDrop = false;
			this->webbrowser->ScriptErrorsSuppressed = false;
			this->webbrowser->WebBrowserShortcutsEnabled = false;
			this->webbrowser->IsWebBrowserContextMenuEnabled = false;
			this->webbrowser->Dock = System::Windows::Forms::DockStyle::Fill;
			this->webbrowser->Location = System::Drawing::Point(0, 25);
			this->webbrowser->Size = System::Drawing::Size(624, 389);
			this->webbrowser->TabIndex = 10;
			this->webbrowser->StatusTextChanged += gcnew System::EventHandler(this, 
														&Form1::webbrowser_statustext_chanaged);
			this->webbrowser->CanGoBackChanged += gcnew System::EventHandler(this, 
														&Form1::webbrowser_can_goback_chanaged);
			this->webbrowser->CanGoForwardChanged += gcnew System::EventHandler(this, 
														&Form1::webbrowser_can_goforward_chanaged);
			this->webbrowser->DocumentTitleChanged += gcnew System::EventHandler(this, 
														&Form1::webbrowser_documenttile_chanaged);
			this->webbrowser->Navigated += gcnew System::Windows::Forms::WebBrowserNavigatedEventHandler( this, 
														&Form1::webbrowser_navigated );

			//Form1 显示按钮
			this->ClientSize = System::Drawing::Size(624, 429);
			this->Controls->Add(this->panel);
			this->Controls->Add(this->webbrowser);
			this->Menu = this->main_menu;
		}

	internal: //内链接
		static property Form1^ GetInstance 
		{
			Form1^ get()
			{
				if ( default_instance_ == nullptr || default_instance_->IsDisposed )
				{
					System::Threading::Monitor::Enter( Form1::typeid );
					try
					{
						if ( default_instance_ == nullptr || default_instance_->IsDisposed )
						{
							default_instance_ = gcnew Form1;
						}
					}
					finally
					{
						System::Threading::Monitor::Exit( Form1::typeid );
					}
				}

				return default_instance_;
			}
		}

		/// <summary>
		/// 清理所有正在使用的资源。
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		static Form1 ^default_instance_;

		void menu_item_file_save_click(System::Object ^, System::EventArgs ^)
		{
			this->webbrowser->ShowSaveAsDialog();
		}

		void textbox_address_keydown(System::Object ^, System::Windows::Forms::KeyEventArgs ^e)
		{
			if (e->KeyCode == System::Windows::Forms::Keys::Enter && !this->textbox_address->Text->Equals(""))
			{
				this->webbrowser->Navigate(textbox_address->Text);
			}
		}

		void button_go_click(System::Object ^, System::EventArgs ^)
		{
			if (!this->textbox_address->Text->Equals(""))
			{
				this->webbrowser->Navigate(textbox_address->Text);
			}
		}

		void button_refresh_click(System::Object ^, System::EventArgs ^)
		{
			if (!this->webbrowser->Url->Equals("about:blank"))
			{
				this->webbrowser->Refresh();
			}
		}

		void button_back_click(System::Object ^, System::EventArgs ^)
		{
			this->webbrowser->GoBack();
		}

		void button_forward_click(System::Object ^, System::EventArgs ^)
		{
			this->webbrowser->GoForward();
		}

		void button_home_click(System::Object ^, System::EventArgs ^)
		{
			this->webbrowser->GoHome();
		}

		void button_stop_click(System::Object ^, System::EventArgs ^)
		{
			this->webbrowser->Stop();
		}

		void webbrowser_statustext_chanaged(System::Object ^, System::EventArgs ^)
		{

		}

		void webbrowser_can_goback_chanaged(System::Object ^, System::EventArgs ^)
		{
			this->button_back->Enabled = this->webbrowser->CanGoBack;
		}

		void webbrowser_can_goforward_chanaged(System::Object ^, System::EventArgs ^)
		{
			this->button_forward->Enabled = this->webbrowser->CanGoForward;
		}

		void webbrowser_documenttile_chanaged(System::Object ^, System::EventArgs ^)
		{
			this->Text = webbrowser->DocumentTitle;
		}

		void webbrowser_navigated(System::Object ^, System::Windows::Forms::WebBrowserNavigatedEventArgs ^)
		{
			this->textbox_address->Text = this->webbrowser->Url->ToString();
		}

		/// <summary>
		/// 必需的设计器变量。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 设计器支持所需的方法 - 不要
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>

#pragma endregion
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
			 }
	};
}

