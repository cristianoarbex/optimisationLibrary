/**
 * Data.cc
 *
 * Copyright(c) 2018
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#include "Data.h"
#include "Options.h"


Data::Data() {
    debug =  Options::getInstance()->getIntOption("debug");
}

Data::~Data() {
}


