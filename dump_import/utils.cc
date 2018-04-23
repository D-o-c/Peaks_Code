#include <sstream>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <syslog.h>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>


#include "utils.h"

using namespace boost::filesystem;
using namespace std;

namespace Utils{
    string get_file_name(const unsigned int &i, const thread::id &ID){
        stringstream t_id;
        t_id << ID;
        return TMP_FOLDER_CSV + t_id.str() + FILENAME.at(i);
    }

    int create_folders(){
        boost::system::error_code returnedError;

        create_directories( TMP_FOLDER_CSV, returnedError );

        if ( returnedError ){
            return -1;  // did not successfully create directories
        }
        else{
            create_directories( ERROR_FOLDER, returnedError );
            if (returnedError){
                return -1;
            }else{
                return 0;
            } // directories successfully created
        }
    }

    void put_in_error(const string &f, const unsigned int &i){
        try{
            std::ofstream error_file;
            std::ifstream actual_file;
            error_file.open(ERROR_FOLDER + string("Errors") + FILENAME.at(i), ios_base::app);
            actual_file.open(f);

            error_file.seekp(0, ios_base::end);
            error_file << actual_file.rdbuf();
            error_file.close();
            actual_file.close();
        }catch (exception &e){
            try{
                boost::random::mt19937 gen(time(0));
                boost::random::uniform_int_distribution<> dist(1000, 10000);

                string rnd_num = to_string(dist(gen));
                copy_file(f, ERROR_FOLDER + rnd_num + FILENAME.at(i), copy_option::fail_if_exists);
            }catch (error_code &e){
                syslog(LOG_CRIT, ("Saving errors during CSV insertion FAILED, data will be lost! - " +
                                  (string)e.message()).c_str());
            }
        }
    }

    vector<string> get_files(const unsigned int &i){
        directory_iterator end_itr;
        vector<string> file_list;

        for (directory_iterator itr(TMP_FOLDER_CSV); itr != end_itr; ++itr){
            if (hasEnding(itr->path().string(), FILENAME.at(i))) {
                string current_file = itr->path().string();
                file_list.push_back(itr->path().string());
            }
        }
        return file_list;
    }

    vector<string> get_dump_files(const path &dump_path){
        directory_iterator end_itr;
        vector<string> file_list;
        int i = 0;

        // cycle through the directory
        for (directory_iterator itr(dump_path); itr != end_itr && i < 500000; ++itr, i++){
            if (itr->path().extension() == ".pgp") {
                string current_file = itr->path().string();
                file_list.push_back(itr->path().string());
            }
        }
        return file_list;
    }

    string getCurrentTime(){
        time_t rawtime;
        struct tm * timeinfo;
        char buffer[80];

        time (&rawtime);
        timeinfo = localtime(&rawtime);

        strftime(buffer,sizeof(buffer),"%x %X:%t",timeinfo);
        string str(buffer);
        return str;
    }

    bool hasEnding (string const &fullString, string const &ending) {
        if (fullString.length() >= ending.length()) {
            return (0 == fullString.compare (fullString.length() - ending.length(), ending.length(), ending));
        } else {
            return false;
        }
    }

}
