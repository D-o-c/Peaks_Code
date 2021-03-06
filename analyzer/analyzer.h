#ifndef ANALYZER_ANALYZER_H
#define ANALYZER_ANALYZER_H


#include "DBStruct.h"
#include "DBManager.h"

class Analyzer {
public:
    Analyzer();
    void analyze_pubkeys(const std::vector<DBStruct::pubkey> &pks) const;
    void analyze_signatures(const std::vector<DBStruct::signatures> &ss) const;

    void analyze_RSA_modulus_common_factor(const std::shared_ptr<DBManager> &dbm, const unsigned int &nThreads);

private:
    void analyze_pubkey(DBStruct::pubkey pk, const std::shared_ptr<DBManager> &dbm) const;
    void analyze_signature(const DBStruct::signatures &sign, const std::shared_ptr<DBManager> &dbm) const;

    void check_RSA(const DBStruct::pubkey &pk, const std::shared_ptr<DBManager> &dbm) const;
    //void check_DSA(const DBStruct::pubkey &pk, const std::shared_ptr<DBManager> &dbm) const;
    //void check_Elgamal(const DBStruct::pubkey &pk, const std::shared_ptr<DBManager> &dbm) const;
    void check_Elgamal_DSA(const DBStruct::pubkey &pk, const std::shared_ptr<DBManager> &dbm) const;
    void check_Curve(const DBStruct::pubkey &pk, const std::shared_ptr<DBManager> &dbm) const;
    bool check_signature(const DBStruct::signatures &sign, const std::shared_ptr<DBManager> &dbm) const;

};


#endif //ANALYZER_ANALYZER_H
