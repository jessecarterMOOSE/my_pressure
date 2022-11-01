#include "MyPressureDemoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
MyPressureDemoApp::validParams()
{
  InputParameters params = MooseApp::validParams();

  return params;
}

MyPressureDemoApp::MyPressureDemoApp(InputParameters parameters) : MooseApp(parameters)
{
  MyPressureDemoApp::registerAll(_factory, _action_factory, _syntax);
}

MyPressureDemoApp::~MyPressureDemoApp() {}

void
MyPressureDemoApp::registerAll(Factory & f, ActionFactory & af, Syntax & syntax)
{
  ModulesApp::registerAll(f, af, syntax);
  Registry::registerObjectsTo(f, {"MyPressureDemoApp"});
  Registry::registerActionsTo(af, {"MyPressureDemoApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
MyPressureDemoApp::registerApps()
{
  registerApp(MyPressureDemoApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
MyPressureDemoApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  MyPressureDemoApp::registerAll(f, af, s);
}
extern "C" void
MyPressureDemoApp__registerApps()
{
  MyPressureDemoApp::registerApps();
}
