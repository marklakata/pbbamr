// This file was generated by Rcpp::compileAttributes
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include <Rcpp.h>

using namespace Rcpp;

// loadheader
List loadheader(std::string filename);
RcppExport SEXP pbbamr_loadheader(SEXP filenameSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::string >::type filename(filenameSEXP);
    __result = Rcpp::wrap(loadheader(filename));
    return __result;
END_RCPP
}
// loadpbi
DataFrame loadpbi(std::string filename, bool loadSNR, bool loadNumPasses, bool loadRQ);
RcppExport SEXP pbbamr_loadpbi(SEXP filenameSEXP, SEXP loadSNRSEXP, SEXP loadNumPassesSEXP, SEXP loadRQSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< std::string >::type filename(filenameSEXP);
    Rcpp::traits::input_parameter< bool >::type loadSNR(loadSNRSEXP);
    Rcpp::traits::input_parameter< bool >::type loadNumPasses(loadNumPassesSEXP);
    Rcpp::traits::input_parameter< bool >::type loadRQ(loadRQSEXP);
    __result = Rcpp::wrap(loadpbi(filename, loadSNR, loadNumPasses, loadRQ));
    return __result;
END_RCPP
}
// loadDataAtOffsets
List loadDataAtOffsets(CharacterVector offsets, std::string bamName, std::string indexedFastaName);
RcppExport SEXP pbbamr_loadDataAtOffsets(SEXP offsetsSEXP, SEXP bamNameSEXP, SEXP indexedFastaNameSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< CharacterVector >::type offsets(offsetsSEXP);
    Rcpp::traits::input_parameter< std::string >::type bamName(bamNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type indexedFastaName(indexedFastaNameSEXP);
    __result = Rcpp::wrap(loadDataAtOffsets(offsets, bamName, indexedFastaName));
    return __result;
END_RCPP
}
// loadHMMfromBAM
List loadHMMfromBAM(CharacterVector offsets, std::string bamName, std::string indexedFastaName, int trimToLength);
RcppExport SEXP pbbamr_loadHMMfromBAM(SEXP offsetsSEXP, SEXP bamNameSEXP, SEXP indexedFastaNameSEXP, SEXP trimToLengthSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< CharacterVector >::type offsets(offsetsSEXP);
    Rcpp::traits::input_parameter< std::string >::type bamName(bamNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type indexedFastaName(indexedFastaNameSEXP);
    Rcpp::traits::input_parameter< int >::type trimToLength(trimToLengthSEXP);
    __result = Rcpp::wrap(loadHMMfromBAM(offsets, bamName, indexedFastaName, trimToLength));
    return __result;
END_RCPP
}
// loadSingleZmwHMMfromBAM
List loadSingleZmwHMMfromBAM(CharacterVector offsets, std::string bamName, std::string indexedFastaName, int windowBreakSize, int minSize);
RcppExport SEXP pbbamr_loadSingleZmwHMMfromBAM(SEXP offsetsSEXP, SEXP bamNameSEXP, SEXP indexedFastaNameSEXP, SEXP windowBreakSizeSEXP, SEXP minSizeSEXP) {
BEGIN_RCPP
    Rcpp::RObject __result;
    Rcpp::RNGScope __rngScope;
    Rcpp::traits::input_parameter< CharacterVector >::type offsets(offsetsSEXP);
    Rcpp::traits::input_parameter< std::string >::type bamName(bamNameSEXP);
    Rcpp::traits::input_parameter< std::string >::type indexedFastaName(indexedFastaNameSEXP);
    Rcpp::traits::input_parameter< int >::type windowBreakSize(windowBreakSizeSEXP);
    Rcpp::traits::input_parameter< int >::type minSize(minSizeSEXP);
    __result = Rcpp::wrap(loadSingleZmwHMMfromBAM(offsets, bamName, indexedFastaName, windowBreakSize, minSize));
    return __result;
END_RCPP
}
