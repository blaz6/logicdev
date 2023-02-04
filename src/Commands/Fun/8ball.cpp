#include "dpp/dpp.h"
#include "../../headers/8ball.h"
#include "curl/curl.h"
#include "nlohmann/json.hpp"

size_t writeCallback(char *ptr, size_t size, size_t nmemb, std::string *userdata)
{
    userdata->append(ptr, size * nmemb);
    return size * nmemb;
}

Ball::~Ball() {
    set_name("8ball");
    set_description("pokaže prihodnost");
}

void Ball::execute(const dpp::slashcommand_t& event) {
    CURL *curl;
    CURLcode res;
    std::string response;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.eightballapi.com/api");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    nlohmann::json json = nlohmann::json::parse(response);
    std::string reading = json.value("reading", "oops");

    dpp::embed embed = dpp::embed()
                    .set_color(dpp::colors::blue_aquamarine)
                    .set_title("cri")
                    .set_description(reading)
                    .set_timestamp(time(nullptr));

    event.reply(dpp::message(event.command.channel_id, embed));
}