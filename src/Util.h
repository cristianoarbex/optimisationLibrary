/**
 * Util.h
 *
 * Copyright(c) 2018 
 * Cristiano Arbex Valle
 * All rights reserved.
 */

#ifndef UTIL_H
#define UTIL_H

// ANSI escape codes to show colours
#define COLOUR_RED     "\x1b[31m"
#define COLOUR_GREEN   "\x1b[32m"
#define COLOUR_YELLOW  "\x1b[33m"
#define COLOUR_BLUE    "\x1b[34m"
#define COLOUR_MAGENTA "\x1b[35m"
#define COLOUR_CYAN    "\x1b[36m"
#define COLOUR_RESET   "\x1b[0m"

// Constantes Gerais
#define INFINITO                  2294967296
#define INFINITO_DOUBLE         2294967296.0
#define TAU                             1e-5
#define TOLERANCE                       1e-6
#define TOLERANCE_VIOLATION             1e-5
#define UND                              "_"

#include <stdlib.h>
#include <stdio.h>
#include <utility>
#include <numeric>
#include <limits>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <map>
#include <utility>
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
//#include <boost/lexical_cast.hpp>
#include <type_traits>
//#include "boost/throw_exception.hpp"

using std::string;
using std::vector;
using std::set;
using std::map;

inline string lex(int l) {
    //return boost::lexical_cast<string>(l);
    return std::to_string(l);
}

// I don't remember why I put this here in the first place. I think it was before C++11 was
// used to I'll comment this code to see if any problem happens. I commented to stop using boost
//#ifdef _WIN32
//namespace boost {
//template<class E> inline void throw_exception(E const & e) {
//  throw e;
//}
//}
//namespace detail {
//
//template<typename T>
//inline std::string
//to_string(T const val, std::false_type /*is_float*/, std::false_type /*is_unsigned*/) {
//    return std::to_string(static_cast<long long>(val));
//}
//
//template<typename T>
//inline std::string
//to_string(T const val, std::false_type /*is_float*/, std::true_type /*is_unsigned*/) {
//    return std::to_string(static_cast<unsigned long long>(val));
//}
//
//template<typename T, typename _>
//inline std::string
//to_string(T const val, std::true_type /*is_float*/, _) {
//    return std::to_string(static_cast<long double>(val));
//}
//
//} // namespace detail
//
//template<typename T>
//inline std::string to_string(T const val) {
//    return detail::io_string(val, std::is_floating_point<T>(), std::is_unsigned<T>());
//}
//#else 
//using std::to_string;
//#endif
//*/

////////////////////////////////////////
////////////////////////////////////////
////////////////////////////////////////

/**
 * Classe responsavel por manter a instancia do problema e avaliar as solucoes.
 */
class Util {

    private:

    public:

        /**
         * Retorna o tempo de sistema.
         */
        static float getTime();
        static double getWallTime();
        static float  getClockTime();
        static const string getCurrentDateTime();

        /**
         * Open and close files
         */
        static bool openFile(FILE**, const char*, const char*);
        static bool closeFile(FILE**);
        static bool fileExists(string);

        /**
         * Exception handler
         */
        static void throwInvalidArgument(string msg, ...);
        static void stop(string msg, ...);

        // 0 success, 1 failure
        static int stringToDouble(string text, double& number);
        static double stringToDouble(string text);

        // General
        static int numDigits(int number);

        // Vectors
        template<typename T>
        static std::vector<T> subVector(std::vector<T> v, int first, int last) {
            typename std::vector<T>::const_iterator beg = v.begin() + first;
            typename std::vector<T>::const_iterator end  = v.begin() + last;
            if (last > (int)v.size()) end = v.end();
            std::vector<T> newVec(beg, end);
            return newVec;
        };
        
        // String functions
        static vector<string> split(const string& i_str, const string& i_delim, int eliminateEmptySubstrings = 1);
        static string join(const vector<string>& strings, const string& separator);
        static string toLowerCase(string data);
        static string toUpperCase(string data);
        static int isNumber(string s); 
        static int isEqual(string s, string c);
        static int startsWith(string s, string start);
        static int contains(vector<string> v, string s);


        // print functions
        static void printIntVector(const vector<int> &vec, int tot = 3, int numPerLine = 0);
        static void printUnsignedVector(const vector<unsigned> &vec, int tot = 3, int numPerLine = 0);
        static void printDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0);
        static void printTwoDoubleVectors(const vector<double> &vec1, const vector<double> &vec2, int tot1 = 5, int dec1 = 2, int tot2 = 5, int dec2 = 2);
        static void printDoubleMatrix(const vector<vector<double> > &vec, int tot = 5, int dec = 2);
        static void printIntMatrix(const vector<vector<int> > &vec, int tot = 5, int printRowNames = 0);
        static void printNonZeroDoubleVector(const vector<double> &vec, int tot = 5, int dec = 2, int numPerLine = 0);
        static void printStringVector(const vector<string> vec, string initialText = "", string separator = " ");

        static void printGraph(const vector<vector<int>> &graph);
        static void printGraph(const vector<vector<double>> &graph, int dec = 2);
 
        static void printFileIntVector(FILE* file, const vector<int> &vec, int numPerLine = 0);
        static void printFileUnsignedVector(FILE* file, const vector<unsigned> &vec, int numPerLine = 0);
        static void printFileDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0);
        static void printFileNonZeroDoubleVector(FILE* file, const vector<double> &vec, int dec = 2, int numPerLine = 0);
      
        /**
         * Ramdon number functions
         */
        static void initialiseSeed(int seed = 0);
        static double getSeed();
        static int randomNumber(int);
        static unsigned long randomLong(unsigned long);
        static double randomNumber(double);
        static int randomAlexandre(int, double*);
        static float randomNumberAlexandre(double*);
        static unsigned long randomLongAlexandre(unsigned long, double*);
        static std::vector<double> randomN(int, bool, double);

        /**
         * Comparators, sorts, permutations
         */
        template <class T1, class T2>
        struct sortPairAsc {
            bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
                return left.second < right.second;
            }
        };

        template <class T1, class T2>
        struct sortPairDesc {
            bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
                return left.second > right.second;
            }
        };


        template <typename T, typename Compare>
        static std::vector<int> sort_permutation(std::vector<T> const& vec, Compare compare) {
            std::vector<int> p(vec.size());
            std::iota(p.begin(), p.end(), 0);
            std::sort(p.begin(), p.end(),
            [&](int i, int j){ return compare(vec[i], vec[j]); });
            return p;
        }

        template <typename T>
        static std::vector<T> apply_permutation(std::vector<T> const& vec,  std::vector<int> const& p) {
            std::vector<T> sorted_vec(p.size());
            std::transform(p.begin(), p.end(), sorted_vec.begin(), [&](int i){ return vec[i]; });
            return sorted_vec;
        }

        template <typename T, typename U>
        static void sortVectorByAnotherVector(vector<T>& vec, const vector<U>& another, int ascending = 1) {
            vector<int> permutation;
            if (ascending) permutation = Util::sort_permutation(another, [](U const& a, U const& b){ return a < b; });
            else           permutation = Util::sort_permutation(another, [](U const& a, U const& b){ return a > b; });
            vec = Util::apply_permutation(vec, permutation);
        }
};    

#endif 
