#include "httplib.h"
#include "json.hpp"
#include "../cpp/sampling.h"
#include "../cpp/cactus.h"

using namespace httplib;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <model_path>" << std::endl;
        return 1;
    }

    std::string model_path = argv[1];

    cactus::cactus_context context;
    common_params params;
    params.model.path = model_path;
    params.n_ctx = 2048;

    if (!context.loadModel(params)) {
        return 1;
    }

    Server svr;

    svr.Post("/v1/chat/completions", [&](const Request& req, Response& res) {
        if (req.body.empty()) {
            res.status = 400;
            return;
        }

        nlohmann::json request_json = nlohmann::json::parse(req.body);

        std::string messages_str = request_json["messages"].dump();
        std::string formatted_prompt = context.getFormattedChat(messages_str, "");

        context.params.prompt = formatted_prompt;
        context.params.sampling.temp = request_json.value("temperature", 0.8);
        context.params.sampling.top_k = request_json.value("top_k", 40);
        context.params.sampling.top_p = request_json.value("top_p", 0.95);
        context.params.sampling.penalty_repeat = request_json.value("frequency_penalty", 1.1);
        context.params.sampling.mirostat = 0;

        context.initSampling();
        context.rewind();
        context.beginCompletion();
        context.loadPrompt();

        std::string completion_text = "";
        while (context.has_next_token && !context.is_interrupted) {
            auto token = context.doCompletion();
            if (token.tok == -1) break;
            completion_text += context.generated_text.substr(completion_text.length());
        }

        json response_json = {
            {"choices", {{
                {"message", {
                    {"role", "assistant"},
                    {"content", completion_text}
                }}
            }}}
        };

        res.set_content(response_json.dump(), "application/json");
    });

    svr.Post("/v1/audio/transcriptions", [&](const Request& req, Response& res) {
        // Placeholder for speech-to-text
        json response_json = {
            {"text", "This is a placeholder for the speech-to-text response."}
        };
        res.set_content(response_json.dump(), "application/json");
    });

    svr.Post("/v1/audio/speech", [&](const Request& req, Response& res) {
        // Placeholder for text-to-speech
        res.set_content("This is a placeholder for the text-to-speech response.", "audio/mpeg");
    });

    std::cout << "Server listening on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}
