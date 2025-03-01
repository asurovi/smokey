//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "smokeyTestApp.h"
#include "smokeyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"

InputParameters
smokeyTestApp::validParams()
{
  InputParameters params = smokeyApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

smokeyTestApp::smokeyTestApp(InputParameters parameters) : MooseApp(parameters)
{
  smokeyTestApp::registerAll(
      _factory, _action_factory, _syntax, getParam<bool>("allow_test_objects"));
}

smokeyTestApp::~smokeyTestApp() {}

void
smokeyTestApp::registerAll(Factory & f, ActionFactory & af, Syntax & s, bool use_test_objs)
{
  smokeyApp::registerAll(f, af, s);
  if (use_test_objs)
  {
    Registry::registerObjectsTo(f, {"smokeyTestApp"});
    Registry::registerActionsTo(af, {"smokeyTestApp"});
  }
}

void
smokeyTestApp::registerApps()
{
  registerApp(smokeyApp);
  registerApp(smokeyTestApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
smokeyTestApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  smokeyTestApp::registerAll(f, af, s);
}
extern "C" void
smokeyTestApp__registerApps()
{
  smokeyTestApp::registerApps();
}
