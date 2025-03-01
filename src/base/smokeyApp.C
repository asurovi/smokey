#include "smokeyApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

InputParameters
smokeyApp::validParams()
{
  InputParameters params = MooseApp::validParams();
  params.set<bool>("use_legacy_material_output") = false;
  params.set<bool>("use_legacy_initial_residual_evaluation_behavior") = false;
  return params;
}

smokeyApp::smokeyApp(InputParameters parameters) : MooseApp(parameters)
{
  smokeyApp::registerAll(_factory, _action_factory, _syntax);
}

smokeyApp::~smokeyApp() {}

void
smokeyApp::registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  ModulesApp::registerAllObjects<smokeyApp>(f, af, s);
  Registry::registerObjectsTo(f, {"smokeyApp"});
  Registry::registerActionsTo(af, {"smokeyApp"});

  /* register custom execute flags, action syntax, etc. here */
}

void
smokeyApp::registerApps()
{
  registerApp(smokeyApp);
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
smokeyApp__registerAll(Factory & f, ActionFactory & af, Syntax & s)
{
  smokeyApp::registerAll(f, af, s);
}
extern "C" void
smokeyApp__registerApps()
{
  smokeyApp::registerApps();
}
