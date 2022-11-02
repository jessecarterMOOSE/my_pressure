//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#pragma once

#include "Action.h"

class MyPressureAction : public Action
{
public:
  MyPressureAction(const InputParameters & params);

  static InputParameters validParams();

  virtual void act() override;

private:
  const FileName _pressure_file;
  const bool _verbose;
  const std::vector<VariableName> _displacements;
};
