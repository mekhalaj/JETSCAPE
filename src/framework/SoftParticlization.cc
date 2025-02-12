/*******************************************************************************
 * Copyright (c) The JETSCAPE Collaboration, 2018
 *
 * Modular, task-based framework for simulating all aspects of heavy-ion collisions
 * 
 * For the list of contributors see AUTHORS.
 *
 * Report issues at https://github.com/JETSCAPE/JETSCAPE/issues
 *
 * or via email to bugs.jetscape@gmail.com
 *
 * Distributed under the GNU General Public License 3.0 (GPLv3 or later).
 * See COPYING for details.
 ******************************************************************************/
// -----------------------------------------
// JETSCPAE module for soft particlization
// This module will generate Monte-Carlo samples for soft hadrons
// -----------------------------------------

#include "SoftParticlization.h"

namespace Jetscape {

SoftParticlization::SoftParticlization() {
    boost_invariance = false;
}

SoftParticlization::~SoftParticlization() {
    for (unsigned i = 0; i < Hadron_list_.size(); i++) {
        Hadron_list_.at(i).clear();
    }
    Hadron_list_.clear();
}

void SoftParticlization::Init() {
    JetScapeModuleBase::Init();
    JSINFO << "Intialize Soft particlization module ... " << GetId() << " ...";
    xml_ = JetScapeXML::Instance()->GetXMLRoot()->FirstChildElement(
                                                        "SoftParticlization");
    if (!xml_) {
        JSWARN << " : Missing XML SoftParticlization section in file!";
        exit(-1);
    }

    boost_invariance = check_boost_invariance();

    InitTask();
}

void SoftParticlization::Exec() {

}

void SoftParticlization::Clear() {
    for (unsigned i = 0; i < Hadron_list_.size(); i++) {
        Hadron_list_.at(i).clear();
    }
    Hadron_list_.clear();
}


bool SoftParticlization::check_boost_invariance() {
    bool boost_invaiance_flag = false;
    auto xml_IS = JetScapeXML::Instance()->GetXMLRoot()->FirstChildElement(
                                                                        "IS");
    double grid_max_z = 0.;
    xml_IS->FirstChildElement("grid_max_z")->QueryDoubleText(&grid_max_z);
    double grid_step_z = 0.1;
    xml_IS->FirstChildElement("grid_step_z")->QueryDoubleText(&grid_step_z);
    int nz = static_cast<int>(2.*grid_max_z/grid_step_z);
    if (nz <= 1) {
        boost_invariance = true;
    }
    return(boost_invaiance_flag);
}


}  // end namespace Jetscape
