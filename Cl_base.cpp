#include "Cl_base.h"
#include "Cl_application.h"

Cl_base::Cl_base(Cl_base* parent, string name)
{
	this->name = name;
	this->parent = parent;

	if (parent != nullptr) //проверка на корневой элемент
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
	if (parent != nullptr) //проверка на корневой элемент
	{
		for (int i = 0; i < parent->children.size(); i++)
		{
			if (parent->children[i] == this)
			{
				parent->children.erase(parent->children.begin() + i); //удаление у нынешнего родителя ребенка с указателем на текущий объект
				break;
			}
		}
	}
	parent = new_parent; //меняем родителя у объекта
	if (parent != nullptr)
	{
		parent->children.push_back(this); //добавляем к новому родителю текущий объект 
	}
}

Cl_base* Cl_base::find_by_name(string name)
{
	if (this->name == name) //проверка имени текущего объекта
		return this;
	for (int i = 0; i < children.size(); i++)
	{
		Cl_base* obj = children[i]->find_by_name(name); //рекурсивный вызов метода для каждого ребенка
		if (obj != nullptr) //если метод для ребенка нашёл объект по имени, то возвращаем результат
		{
			return obj;
		}
	}
	return nullptr; //если не находим объект с таким именем
}

bool Cl_base::set_state(int state)
{
	if (parent != nullptr && parent->get_state() == 0) //если объект не корневой и его состояние 0, возвращаем false
	{
		return false;
	}
	if (state == 0) //если параметр 0, то выключаем все объекты вниз по иерархии
	{
		for (Cl_base* child : children)
		{
			child->set_state(0);
		}
	}
	this->state = state; //присваиваем состоянию объекта переданный параметр
	return true;
}

void Cl_base::print_tree(int lvl)
{
	if (parent != nullptr) //если объект не корневой 
	{
		cout << endl;
	}
	else
	{
		cout << "Object tree\n";
	}
	for (int i = 0; i < lvl * 4; i++) //вывод пробелов в соответсвии с уровнем
	{
		cout << " ";
	}
	cout << name; //вывод имени объекта
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->print_tree(lvl + 1); //рекурсивный вызов метода для каждого ребенка
	}
}

void Cl_base::print_tree_with_state(int lvl)
{
	if (parent != nullptr) //если объект не корневой 
	{
		cout << endl;
	}
	else
	{
		cout << "\nThe tree of objects and their readiness\n";
	}
	for (int i = 0; i < lvl * 4; i++) //вывод пробелов в соответсвии с уровнем
	{
		cout << " ";
	}
	cout << name; //вывод имени объекта
	if (get_state() != 0) //проверка состояния объекта
	{
		cout << " is ready";
	}
	else
	{
		cout << " is not ready";
	}
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->print_tree_with_state(lvl + 1); //рекурсивный вызов метода для каждого ребенка
	}
}

Cl_base* Cl_base::get_root()
{
	Cl_base* temp = this;
	while (temp->parent != nullptr) //поднимаемся вверх по иерархии пока не дойдем до корневого
	{
		temp = temp->parent;
	}
	return temp; //указатель на корневой объект 
}

Cl_base* Cl_base::find_by_path(string path)
{
	Cl_base* temp = this;
	if (path == "") //проверка на пустую строку
	{
		return nullptr;
	}
	if (path == ".") //точка - вернуть указатель на текущий
	{
		return this;
	}
	if (path == "/") // / - вернуть указатель на корневой
	{
		return get_root();
	}
	if (path.substr(0, 2) == "//") // // - получаем указатель на корневой и выполняем поиск объекта по имени
	{
		return get_root()->find_by_name(path.substr(2));
	}
	if (path[0] == '/')
	{
		temp = get_root()->find_by_path(path.substr(1)); //temp присваиваем рузельтат рекурсивного вызова метода от строки без /
		if (temp) //если результат вызова не нулевой указатель, то вернуть результат
		{
			return temp;
		}
	}
	if (path.find("/") != string::npos) // проверка на наличие в строке /
	{
		for (int i = 0; i < children.size(); i++)
		{
			if (children[i]->get_name() == path.substr(0, path.find("/"))) // ищем у текущего объекта ребенка с именем, указанным в пути
			{
				temp = children[i]->find_by_path(path.substr(path.find("/") + 1)); //вызываем метод от объекта по указателю children[i] с новым путем
				if (temp) //если результат вызова не нулевой указатель, то вернуть результат
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

void Cl_base::set_state_all() //метод включения всех объектов
{
	set_state(1);
	for (int i = 0; i < children.size(); i++)
	{
		children[i]->set_state_all();
	}
}
string Cl_base::get_path(string path) //метод получения абсолютного пути объекта
{
	if (parent == nullptr)
	{
		return "/";
	}
	return parent->get_path("/") + name + path;
}
void Cl_base::set_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler)
{
	for (int i = 0; i < connects.size(); i++) // проверка на наличие уже такого соединения
	{
		if (connects[i]->signal == signal && connects[i]->obj == obj && connects[i]->handler == handler)
		{
			return;
		}
	} //если такого соединения нет, создаем и добавляем его в вектор соединений
	s_connect* temp = new s_connect();
	temp->signal = signal;
	temp->obj = obj;
	temp->handler = handler;
	connects.push_back(temp);
}
void Cl_base::delete_connect(TYPE_SIGNAL signal, Cl_base* obj, TYPE_HANDLER handler)
{
	for (int i = 0; i < connects.size(); i++) // ищем соединение
	{
		if (connects[i]->signal == signal && connects[i]->obj == obj && connects[i]->handler == handler) //если находим заданное соединение, то
		{
			connects.erase(connects.begin() + 1);//удаляем его
			return;
		}
	}
}

void Cl_base::emit_signal(TYPE_SIGNAL signal, string& command) //метод выдачи сигнала
{
	if (connects.size() == 0) //проверка наличия связей
	{
		return;
	}
	if (!state) // проверка включения объекта
	{
		return;
	}
	(this->*signal)(command); //установка сигнала

	for (int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->signal == signal && connects[i]->obj->state != 0)
		{ // если целевой объект вкл, то выполняется обработка сигнала
			(connects[i]->obj->*(connects[i]->handler))(command);
		}
	}
}
