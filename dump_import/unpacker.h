#ifndef UNPACKER_UNPACKER_H
#define UNPACKER_UNPACKER_H


#include <Key.h>
#include <Packets/Packet.h>
#include <bits/shared_ptr.h>
#include "DBManager.h"
#include "DBStruct.h"


namespace Unpacker {

    void unpack_dump_th(const std::vector<std::string> &files);
    void unpack_dump(std::ifstream &key_file, const std::shared_ptr<DBManager> &dbm);
    DBStruct::signatures get_signature_data(const OpenPGP::Key::SigPairs::iterator &sp, const OpenPGP::Packet::Key::Ptr &priKey, const std::string &uatt_id = "");
    DBStruct::pubkey get_publicKey_data(const OpenPGP::Packet::Tag::Ptr &p, const OpenPGP::Packet::Key::Ptr &priKey);
    DBStruct::userID get_userID_data(const OpenPGP::Packet::Tag::Ptr &user_pkt, const OpenPGP::Packet::Key::Ptr &key);
    void get_userAttributes_data(const OpenPGP::Packet::Tag::Ptr &p, DBStruct::userAtt &ua_struct);
    void read_gpg_keyserver_data(const OpenPGP::Key::Ptr &k, DBStruct::gpg_keyserver_data *gk);
    void get_tag2_subpackets_data(const std::vector<OpenPGP::Subpacket::Tag2::Sub::Ptr> &subps, DBStruct::signatures *ss);

    void handle_wrong_sig(DBStruct::signatures &ss, const OpenPGP::Packet::Key::Ptr &key, const OpenPGP::Packet::User::Ptr &user,
                          const OpenPGP::Packet::Tag2::Ptr &sig);
    void handle_wrong_sig(DBStruct::signatures &ss, const OpenPGP::Packet::Key::Ptr &key, const OpenPGP::Packet::Key::Ptr &subkey,
                          const OpenPGP::Packet::Tag2::Ptr &sig);


    OpenPGP::PGP::Packets get_ordered_packet(OpenPGP::PGP::Packets packet_list);
    std::string concat(const OpenPGP::PGP::Packets &packet_list);
    bool compare(const OpenPGP::Packet::Tag::Ptr &p1, const OpenPGP::Packet::Tag::Ptr &p2);
};

#endif //UNPACKER_UNPACKER_H
