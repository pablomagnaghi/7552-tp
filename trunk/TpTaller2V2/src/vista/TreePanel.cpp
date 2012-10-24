
#include "Ide.h"
#include "TreePanel.h"

TreePanel::TreePanel(const Glib::RefPtr<Gtk::Builder>& Ide_b, Ide* i) :
		ide(i), Ide_builder(Ide_b) {
	add_events(Gdk::ALL_EVENTS_MASK);
	this->enlazarWidgets();
	this->show();
}

bool TreePanel::regenerar() {
	this->limpiar();

	if (!this->hayProyecto()) {
		return false;
	}

	VistaDiagrama * principal = this->ide->getProyecto()->getDiagramaPrincipal();

	Gtk::TreeModel::Row row = *(this->refTreeModel->append());
	row[this->m_Columnas.m_col_Nombre] = principal->getNombre();
	row[this->m_Columnas.m_col_vDiag_Pointer] = principal;
	row[this->m_Columnas.m_col_esDiag] = true;
	this->regenerarRecur(principal, &row);
	return true;
}

void agregarItemAlTreeModel(const std::string, VistaComponente *, bool esDiagrama) {

}

void TreePanel::regenerarRecur(VistaDiagrama* diag, Gtk::TreeModel::Row *row) {
	std::string nombre;
	//primero cargo los componentes de ese diag y luego los diag hijos
	vector<VistaComponente*>::iterator itComp = diag->componentesBegin();
	vector<VistaComponente*>::iterator compEnd = diag->componentesEnd();
	while (itComp != compEnd) {
		Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(row->children()));
		nombre = (*itComp)->getNombre();
		std::cout << nombre << std::endl;
		if (nombre != "") {
			rowSec[this->m_Columnas.m_col_Nombre] = nombre;
			rowSec[this->m_Columnas.m_col_vComp_Pointer] = *itComp;
			rowSec[this->m_Columnas.m_col_esDiag] = false;
		}
		itComp++;
	}

	//cargo el sub diagrama y lurgo regenerar recur sobre ese
	vector<VistaDiagrama*>::iterator itHijos = diag->vdiagramasBegin();
	vector<VistaDiagrama*>::iterator HijosEnd = diag->vdiagramasEnd();
	while (itHijos != HijosEnd) {
		Gtk::TreeModel::Row rowSec = *(this->refTreeModel->append(row->children()));
		rowSec[this->m_Columnas.m_col_Nombre] = (*itHijos)->getNombre();
		rowSec[this->m_Columnas.m_col_vDiag_Pointer] = (*itHijos);
		rowSec[this->m_Columnas.m_col_esDiag] = true;
		this->regenerarRecur((VistaDiagrama*) (*itHijos), &rowSec);
		itHijos++;
	}
}

TreePanel::~TreePanel() {
	// TODO Auto-generated destructor stub
}

void TreePanel::enlazarWidgets() {
	Gtk::ScrolledWindow* sTpanel;
	this->Ide_builder->get_widget("scroll_treePanel", sTpanel);
	this->refTreeModel = Gtk::TreeStore::create(this->m_Columnas);
	this->set_model(this->refTreeModel);
	this->append_column("Componentes", this->m_Columnas.m_col_Nombre);
	sTpanel->add(*this);
}

bool TreePanel::on_button_press_event(GdkEventButton* event) {
	if (!this->hayProyecto())
		return true;
	Gtk::TreeView::on_button_press_event(event);
	//Doble click izquierdo
	if (event->type == GDK_2BUTTON_PRESS) {
		Glib::RefPtr<Gtk::TreeSelection> refTreeSelection = this->get_selection();
		Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
		if (iter) //If anything is selected
		{
			//Hay que distinguir entre diagramas y componentes
			bool esDiagrama = (*iter)[this->m_Columnas.m_col_esDiag];
			if (esDiagrama) {
				VistaDiagrama *diagPointer = (*iter)[this->m_Columnas.m_col_vDiag_Pointer];
				this->ide->cargarDiagrama((VistaDiagrama*) diagPointer);
			} else {
				Gtk::TreeModel::iterator parentIter;
				parentIter = (*iter)->parent();
				//Se supone que tiene que ser un diagrama
				if (((*parentIter)[this->m_Columnas.m_col_esDiag]) == true) {
					VistaDiagrama *diagPointer = (*parentIter)[this->m_Columnas.m_col_vDiag_Pointer];
					this->ide->cargarDiagrama((VistaDiagrama*) diagPointer);
				}
			}
			//string s = (*iter)[this->m_Columnas.m_col_Nombre];
			//cout<<s<<(*iter)[this->m_Columnas.m_col_Diag_Pointer] <<"    "<<(*iter)[this->m_Columnas.m_col_esDiag]<<endl;
			//Gtk::TreeModel::Row row = *iter;
			//this->refTreeModel->erase(iter);
		}
	} else if ((event->type == GDK_BUTTON_PRESS) && (event->button == 3)) {
		Gtk::TreeModel::Path seleccion;
		if (this->get_path_at_pos(event->x, event->y, seleccion)) {
			//
			this->lanzarPopup(event);
		}
	}
	return true;
}

void TreePanel::lanzarPopup(GdkEventButton* event) {

	// CREO MENU POPUP (Ver dependiendo que se clickeo)
	Glib::RefPtr<Gtk::ActionGroup> actionGroup;

	Gtk::Menu * m_pMenuPopup;
	Glib::RefPtr<Gtk::UIManager> userInterfaceManager;

	actionGroup = Gtk::ActionGroup::create();

	actionGroup->add(Gtk::Action::create("ContextMenu", "Context Menu"));

	actionGroup->add(Gtk::Action::create("ContextAgregarDiagrama", "Agregar Diagrama Hijo"),
			sigc::mem_fun(*this, &TreePanel::on_popup_boton_agregar_diagrama_hijo));

	actionGroup->add(Gtk::Action::create("ContextEliminarDiagrama", "Eliminar Diagrama"),
			sigc::mem_fun(*this, &TreePanel::on_popup_boton_eliminar_diagrama));

	userInterfaceManager = Gtk::UIManager::create();
	userInterfaceManager->insert_action_group(actionGroup);

	//Layout the actions in a menubar and toolbar:
	Glib::ustring ui_info = "<ui>"
			"  <popup name='PopupMenu'>"
			"    <menuitem action='ContextAgregarDiagrama'/>"
			"    <menuitem action='ContextEliminarDiagrama'/>"
			"  </popup>"
			"</ui>";
	try {
		userInterfaceManager->add_ui_from_string(ui_info);
	} catch (const Glib::Error& ex) {
		std::cerr << "building menus failed: " << ex.what();
	}

	// LANZO MENU POPUP
	m_pMenuPopup = dynamic_cast<Gtk::Menu*>(userInterfaceManager->get_widget("/PopupMenu"));

	if (!m_pMenuPopup)
		g_warning("menu not found");
	else
		m_pMenuPopup->popup(event->button, event->time);
}

void TreePanel::on_popup_boton_agregar_diagrama_hijo() {

}

void TreePanel::on_popup_boton_eliminar_diagrama() {

}

bool TreePanel::hayProyecto() {
	return this->ide->getProyecto() != NULL;
}

void TreePanel::limpiar() {
	this->refTreeModel->clear();
}
