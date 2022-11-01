//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "MyPressureDemoTestApp.h"
#include "MyPressureDemoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

InputParameters
MyPressureDemoTestApp::validParams()
{
  InputParameters params = MyPressureDemoApp::validParams();
  return params;
}

MyPressureDemoTestApp::MyPressureDemoTestApp(InputParameters parameters) : MooseApp(parameters)
{
  MyPressureDemoTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

MyPressureDemoTestApp::~MyPressureDemoTestApp() {}

void
MyPressureDemoTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  MyPressureDemoApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"MyPressureDemoTestApp"});
    Registry::registerActionsTo(af, {"MyPressureDemoTestApp"});
  }
}

void
MyPressureDemoTestApp::registerApps()
{
  registerApp(MyPressureDemoApp);
  registerApp(MyPressureDemoTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
MyPressureDemoTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  MyPressureDemoTestApp::registerAll(f, af, s);
}
extern "C" void
MyPressureDemoTestApp__registerApps()
{
  MyPressureDemoTestApp::registerApps();
}
