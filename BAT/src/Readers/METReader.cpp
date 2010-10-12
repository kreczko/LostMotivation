/*
 * METReader.cpp
 *
 *  Created on: 4 Aug 2010
 *      Author: kreczko
 */

#include "../../interface/Readers/METReader.h"

namespace BAT {
const std::string METReader::algorithmPrefixes[MET::NUMBER_OF_METALGORITHMS] = {
        "mets",
        "metsKT4",
        "metsKT6",
        "tcmets",
        "PFMets" };

METReader::METReader() :
    exReader(), eyReader(), met() {

}

METReader::METReader(TChainPointer input, MET::Algorithm algo) :
    exReader(input, algorithmPrefixes[algo] + "_ex"),
    eyReader(input, algorithmPrefixes[algo] + "_ey") {

}

METReader::~METReader() {
}

void METReader::initialise() {
    exReader.initialise();
    eyReader.initialise();
}

const METPointer METReader::getMET() {
    readMET();
    return met;
}

void METReader::readMET() {
    met = METPointer(new MET(exReader.getVariableAt(0), eyReader.getVariableAt(0)));
}
}
