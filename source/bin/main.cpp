
#include <cfg/cmd_source.hpp>
#include <cfg/settings.hpp>
#include <meta/info.hpp>
#include <mkt/reg_var_str.hpp>
#include <mkt/source.hpp>
#include <ref/database.hpp>

#include "mktview/version.hpp"

using namespace miu;

int32_t main(int32_t argc, const char* argv[]) try {
    mkt::reg_var_str();

    cfg::cmd_source source { argc, argv };
    cfg::settings settings { &source };

    if (settings.optional<bool>("version", false)) {
        std::cout << mktview::version() << std::endl;

    } else if (settings.optional<bool>("usage", false)) {
        std::cout << mktview::version() << std::endl;
        std::cout << mktview::build_info() << std::endl;
        std::cout << meta::info() << ": subscribe to mkt adapter" << std::endl;
        std::cout << "\nUsage: mktview <mkt adapter name>" << std::endl;

    } else {
        auto mkt_name = settings.required<std::string>(0);
        auto symbols  = settings.optional<cfg::settings>("symbols", {});

        auto source   = mkt::source { mkt_name };
        auto database = ref::database::open(source.db_name(), shm::mode::READ);

        std::cout << "database: " << database.name() << std::endl;

        std::vector<mkt::topic> topics;
        if (symbols) {
            for (auto i = 0U; i < symbols.size(); i++) {
                ref::symbol symbol { symbols.required<std::string>(i) };
                topics.push_back(source.subscribe(symbol));
            }
        } else {
            for (auto i = 0U; i < database.num_of_instrument(); i++) {
                topics.push_back(source.subscribe(i));
            }
        }

        while (1) {
            for (auto& topic : topics) {
                if (topic.refresh()) {
                    std::cout << com::to_string(topic) << std::endl;
                }
            }
        }
    }

    return 0;
} catch (std::exception const& err) {
    std::cerr << err.what() << std::endl;
    return -1;
} catch (...) {
    std::cerr << "unknown error" << std::endl;
    return -1;
}
