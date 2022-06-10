

#include "DataConcreteMixerTruckRouting.h"
#include "Options.h"

DataConcreteMixerTruckRouting::DataConcreteMixerTruckRouting() : Data(){
    numberOfConstructions = 0;
    concreteMixerTruckFleet = 0;
    numberOfTypesOfConcrete = 0;
}

DataConcreteMixerTruckRouting::~DataConcreteMixerTruckRouting() {
}

void DataConcreteMixerTruckRouting::readData() {
    if (debug) printf("Initializing data for Concrete Mixer Routing \n\n");

    FILE* file;
    string inputFilename = Options::getInstance()->getStringOption("input");
    string fourLastCharacters = inputFilename.substr(inputFilename.length() - 4);
    string availableSuffix = ".txt";

    // empty filename
    if (inputFilename.c_str() == NULL || inputFilename.find_first_not_of(' ') == std::string::npos) Util::throwInvalidArgument("Error: Input file '%s' has an  invalid name.", inputFilename.c_str());

    // input format
    if (std::count(fourLastCharacters.begin(), fourLastCharacters.end(), '.') == 0) inputFilename.append(availableSuffix);
    if (inputFilename.compare(inputFilename.size() - availableSuffix.size(), availableSuffix.size(), availableSuffix) != 0) Util::throwInvalidArgument("Error: Input file '%s' is in invalid format.", inputFilename.c_str());
 
    // opening file
    if (!Util::openFile(&file, inputFilename.c_str(), "r")) Util::throwInvalidArgument("Error: Input file '%s' was not found or could not be opened.", inputFilename.c_str());

    try {
        char buffer[50];
        // number of constructions
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%d", &numberOfConstructions       ) != 1) throw std::invalid_argument("");

        // concrete mixer truck fleet
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%d", &concreteMixerTruckFleet     ) != 1) throw std::invalid_argument("");

        // number of types of concrete
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%d", &numberOfTypesOfConcrete     ) != 1) throw std::invalid_argument("");

        // fixed cost of using the concrete mixer truck
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%lf", &fixedCost                  ) != 1) throw std::invalid_argument("");

        // concrete mixer truck capacity
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%s", buffer                       ) != 1) throw std::invalid_argument("");
        if (fscanf(file, "%lf", &concreteMixerTruckCapacity ) != 1) throw std::invalid_argument("");

        demands   .resize(numberOfConstructions + 1                                           );
        distances .resize(numberOfConstructions + 1, vector<double>(numberOfConstructions + 1));

        // demands
        if (fscanf(file, "%s", buffer                                                 ) != 1) throw std::invalid_argument("");
        for (int i = 0; i <= numberOfConstructions; i++) {
            if (fscanf(file, "%d", &demands[i].constructionId                         ) != 1) throw std::invalid_argument("");
            if (fscanf(file, "%lf", &demands[demands[i].constructionId].quantity      ) != 1) throw std::invalid_argument("");
            if (fscanf(file, "%d", &demands[demands[i].constructionId].concreteTypeId ) != 1) throw std::invalid_argument("");
        }

        // distances
        if (fscanf(file, "%s", buffer                    ) != 1) throw std::invalid_argument("");
        for (int i = 0; i <= numberOfConstructions; i++) {
            for (int j = 0; j <= numberOfConstructions; j++) {
                if (fscanf(file, "%lf", &distances[i][j] ) != 1) throw std::invalid_argument("");
            }
        }

    } catch ( const std::invalid_argument& e) {
        if (!Util::closeFile(&file)) Util::throwInvalidArgument("Error: Instances file %s could not be closed.", inputFilename.c_str());
        Util::throwInvalidArgument("Error: Instances file '%s' is invalid.", inputFilename.c_str());
    }

    // close file
    if (!Util::closeFile(&file)) Util::throwInvalidArgument("Error: Instances file %s could not be closed.", inputFilename.c_str());
}

void DataConcreteMixerTruckRouting::print() {
    if (debug) {
        printf("number of constructions\n");
        printf("%d\n\n", numberOfConstructions);
        printf("concrete mixer truck fleet\n");
        printf("%d\n\n", concreteMixerTruckFleet);
        printf("number of types of concrete\n");
        printf("%d\n\n", numberOfTypesOfConcrete);
        printf("fixed cost of using the concrete mixer truck\n");
        printf("R$%.2f\n\n", fixedCost);
        printf("concrete mixer truck capacity\n");
        printf("%.2f\n\n", concreteMixerTruckCapacity);
        printf("demands\n");
        for (int i = 0; i <= numberOfConstructions; i++) {
            printf("demandId: %d\t quantity: %.2f\t concreteTypeId: %2d\n", demands[i].constructionId, demands[i].quantity, demands[i].concreteTypeId);
        }
        printf("\ndistances\n");
        for (int i = 0; i <= numberOfConstructions; i++) {
            for (int j = 0; j <= numberOfConstructions; j++) {
                printf("%.2f\t", distances[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }

}

ClientDemand DataConcreteMixerTruckRouting::getDemand(int i) const {
    if (i >= numberOfConstructions + 1) Util::throwInvalidArgument("Error: Out of range parameter i in getDemand");
    return demands[i];
}

double DataConcreteMixerTruckRouting::getDistance(int i, int j) const {
    if (i >= numberOfConstructions + 1) Util::throwInvalidArgument("Error: Out of range parameter i in getDistance");
    if (j >= numberOfConstructions + 1) Util::throwInvalidArgument("Error: Out of range parameter j in getDistance");
    return distances[i][j];
}
