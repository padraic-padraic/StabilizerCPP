#include <boost/program_options.hpp>
#include <iostream>
#include <typeinfo>


int main(int argc, char *argv[]) {
    //Comment out as this wasn't building but the tests will run!
//    namespace po = boost::program_options;
//    po::positional_options_description pdesc;
//    pdesc.add("nQubits", 1);
//    po::options_description desc("StabilizerCPP:\n Quickly generate Stabilizer Groups for the desired number of qubits. \n\n Allowed Options:");
//    desc.add_options()
//        ("help", "Produce this message")
//            ("input-file", "Specify file path for writing out.")
//    ;
//    po::variables_map vm;
//    po::store(po::command_line_parser(argc, argv).
//            options(desc).positional(pdesc).run(), vm);
//    if (vm.count("help") || argc==0){
//        std::cout << desc << std::endl;
//    }
    return 0;
}
