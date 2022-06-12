#include "Cl_base.h"
#include "Cl_application.h"

Cl_base::Cl_base(Cl_base* parent, string name)
{
	this->name = name;
	this->parent = parent;

	if (parent != nullptr) //�������� �� �������� �������
	{
		parent->children.push_back(this);
	}
}

Cl_base::~Cl_base()
{
	for (int i = 0; i < children.size(); i++)
	{
		delete children[i];
	}
	//for (Cl_base* ch:children)  
	//	delete ch;

	//for (vector <Cl_base*>::iterator it = children.begin(); i < children.end(); i++)
	//	delete *it;
}

void Cl_base::print()
{
	if (children.size() > 0)
	{
		cout << endl << get_name();
		for (int i = 0; i < children.size(); i++)
		{
			cout << "  " << children[i]->get_name();
		}
		for (int i = 0; i < children.size(); i++)
		{
			children[i]->print();
		}
	}
}

void Cl_base::set_parent(Cl_base* new_parent)
{
	if (parent != nullptr) //�������� �� �������� �������
	{
		for (int i = 0; i < parent->children.size(); i++)
		{
			if (parent->children[i] == this)
			{
				parent->children.erase(parent->children.begin() + i); //�������� � ��������� �������� ������� � ���������� �� ������� ������
				break;
			}
		}
	}
	parent = new_parent; //������ �������� � �������
	if (parent != nullptr)
	{
		parent->children.push_back(this); //��������� � ������ �������� ������� ������ 
	}
}

Cl_base* Cl_base::find_by_name(string name)
{
	if (this->name == name) //�������� ����� �������� �������
		return this;
	for (int i = 0; i < children.size(); i++)
	{
		Cl_base* obj = children[i]->find_by_name(name); //����������� ����� ������ ��� ������� �������
		if (obj != nullptr) //���� ����� ��� ������� ����� ������ �� �����, �� ���������� ���������
		{
			return obj;
		}
	}
	return nullptr; //���� �� ������� ������ � ����� ������
}

bool Cl_base::set_state(int state)
{
	if (parent != nullptr && parent->get_state() == 0) //���� ������ �� �������� � ��� ��������� 0, ���������� false
	{
		return false;
	}
	if (state == 0) //���� �������� 0, �� ��������� ��� ������� ���� �� ��������
	{
		for (Cl_base* child : children)
		{
			child->set_state(0);
		}
	}
	this->state = state; //����������� ��������� ������� ���������� ��������
	return true;
}

void Cl_base::print_tree(int lvl)
{
	if (parent != nullptr) //���� ������ �� �������� 
	{
		cout << endl;
	}
	else
	{
		cout << "Object tree\n";
	}
	for (int i = 0; i < lvl * 4; i++) //����� �������� � ����������� � �������
	{
		cout << " ";
	}
	cout << name; //����� ����� �������
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->print_tree(lvl + 1); //����������� ����� ������ ��� ������� �������
	}
}

void Cl_base::print_tree_with_state(int lvl)
{
	if (parent != nullptr) //���� ������ �� �������� 
	{
		cout << endl;
	}
	else
	{
		cout << "\nThe tree of objects and their readiness\n";
	}
	for (int i = 0; i < lvl * 4; i++) //����� �������� � ����������� � �������
	{
		cout << " ";
	}
	cout << name; //����� ����� �������
	if (get_state() != 0) //�������� ��������� �������
	{
		cout << " is ready";
	}
	else
	{
		cout << " is not ready";
	}
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->print_tree_with_state(lvl + 1); //����������� ����� ������ ��� ������� �������
	}
}

Cl_base* Cl_base::get_root()
{
	Cl_base* temp = this;
	while (temp->parent != nullptr) //����������� ����� �� �������� ���� �� ������ �� ���������
	{
		temp = temp->parent;
	}
	return temp; //��������� �� �������� ������ 
}

Cl_base* Cl_base::find_by_path(string path)
{
	Cl_base* temp = this;
	if (path == "") //�������� �� ������ ������
	{
		return nullptr;
	}
	if (path == ".") //����� - ������� ��������� �� �������
	{
		return this;
	}
	if (path == "/") // / - ������� ��������� �� ��������
	{
		return get_root();
	}
	if (path.substr(0, 2) == "//") // // - �������� ��������� �� �������� � ��������� ����� ������� �� �����
	{
		return get_root()->find_by_name(path.substr(2));
	}
	if (path[0] == '/')
	{
		temp = get_root()->find_by_path(path.substr(1)); //temp ����������� ��������� ������������ ������ ������ �� ������ ��� /
		if (temp) //���� ��������� ������ �� ������� ���������, �� ������� ���������
		{
			return temp;
		}
	}
	if (path.find("/") != string::npos) // �������� �� ������� � ������ /
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i]->get_name() == path.substr(0, path.find("/"))) // ���� � �������� ������� ������� � ������, ��������� � ����
			{
				temp = children[i]->find_by_path(path.substr(path.find("/") + 1)); //�������� ����� �� ������� �� ��������� children[i] � ����� �����
				if (temp) //���� ��������� ������ �� ������� ���������, �� ������� ���������
				{
					return temp;
				}
			}
		}
	}
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->get_name() == path)
		{
			return children[i];
		}
	}
	return nullptr;
}

void Cl_base::set_state_all() //����� ��������� ���� ��������
{
	set_state(1);
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->set_state_all();
	}
}
string Cl_base::get_path(string path) //����� ��������� ����������� ���� �������
{
	if (parent == nullptr)
	{
		return "/";
	}
	return parent->get_path("/") + name + path;
}
void Cl_base::set_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler)
{
	for (int i = 0; i < connects.size(); i++) // �������� �� ������� ��� ������ ����������
	{
		if (connects[i]->signal == signal && connects[i]->obj == obj && connects[i]->handler == handler)
		{
			return;
		}
	} //���� ������ ���������� ���, ������� � ��������� ��� � ������ ����������
	s_connect* temp = new s_connect();
	temp->signal = signal;
	temp->obj = obj;
	temp->handler = handler;
	connects.push_back(temp);
}
void Cl_base::delete_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler)
{
	for (int i = 0; i < connects.size(); i++) // ���� ����������
	{
		if (connects[i]->signal == signal && connects[i]->obj == obj && connects[i]->handler == handler) //���� ������� �������� ����������, ��
		{
			connects.erase(connects.begin() + 1);//������� ���
			return;
		}
	}
}

void Cl_base::emit_signal(TYPE_SIGNAL signal, string& command) //����� ������ �������
{
	if (connects.size() == 0) //�������� ������� ������
	{
		return;
	}
	if (!state) // �������� ��������� �������
	{
		return;
	}
	(this->*signal)(command); //��������� �������

	for (int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->signal == signal && connects[i]->obj->state != 0)
		{ // ���� ������� ������ ���, �� ����������� ��������� �������
			(connects[i]->obj->*(connects[i]->handler))(command);
		}
	}
}
