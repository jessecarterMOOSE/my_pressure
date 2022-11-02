//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "MyPressureAction.h"
#include "Factory.h"
#include "Parser.h"
#include "FEProblem.h"
#include "MooseObjectAction.h"

registerMooseAction("MyPressureDemoApp", MyPressureAction, "meta_action");

InputParameters
MyPressureAction::validParams()
{
  InputParameters params = Action::validParams();
  params.addRequiredParam<FileName>("pressure_file", "Name of file containing pressure and surface information.");
  params.addParam<bool>("verbose", false, "Print out more information.");
  return params;
}

MyPressureAction::MyPressureAction(const InputParameters & params)
  : Action(params),
    _pressure_file(getParam<FileName>("pressure_file")),
    _verbose(getParam<bool>("verbose"))
{
}

void
MyPressureAction::act()
{
  if (_current_task == "meta_action")
  {
    std::cout<<"current_task: "<<_current_task<<std::endl;

    // pretend these came from file
    std::string boundary_name = "top";
    std::string function_name = "linear_ramp";
    std::string factor_string = "-2.0";

    // set action parameters
    if (_verbose)
      std::cout<<"adding action parameters..."<<std::endl;
    auto action_params = _action_factory.getValidParams("PressureAction");
    action_params.set<std::vector<BoundaryName>>("boundary") = {boundary_name};
    action_params.set<FunctionName>("function") = function_name;
    action_params.set<Real>("factor") = std::stod(factor_string);

    if (_verbose)
      std::cout<<"allocating action..."<<std::endl;
    auto action = MooseSharedNamespace::static_pointer_cast<MooseObjectAction>(
      _action_factory.create("PressureAction", boundary_name+"_action", action_params));

    if (_verbose)
      std::cout<<"addActionBlock(action)..."<<std::endl;
    _awh.addActionBlock(action);
  }
}
