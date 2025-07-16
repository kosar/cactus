# Using the Cactus Project

This document provides a thorough explanation of how to use the Cactus project to run a new model in GGUF format from Hugging Face. It covers the project's architecture, how to run a new GGUF model, how to build and run the C++ example, how to expose the model as a web server, how to integrate a speech-to-text model, and how to use multi-modal models.

## 1. Project Overview

This project, called "Cactus," is a cross-platform framework for running large language models (LLMs) and other AI models locally on your devices. It's designed to be efficient and work on a variety of hardware, from smartphones to laptops. Here's a breakdown of its architecture and how the different components work together:

### 1.1. Core C++ Engine

At the heart of Cactus is a powerful C++ engine that handles all the heavy lifting. This engine is built on top of the popular `llama.cpp` library, which is known for its high performance and efficiency in running LLMs. The C++ core is responsible for:

*   **Model Loading:** Loading GGUF-formatted models into memory. GGUF is a file format specifically designed for `llama.cpp` that allows for fast loading and memory-mapping.
*   **Inference:** Running the model to generate text, embeddings, or other outputs. The C++ engine is optimized for both CPU and GPU execution, so it can take advantage of the available hardware to speed up inference.
*   **Chat and Prompt Formatting:** The engine includes logic for formatting chat messages into the specific prompt format required by the model. This is essential for having a coherent conversation with the model.
*   **Multi-modal Support:** The C++ core can also handle multi-modal models that can process both text and images. This allows you to build applications that can "see" and understand the world around them.
*   **TTS (Text-to-Speech):** The engine also supports text-to-speech models, which can convert text into spoken audio.

### 1.2. Foreign Function Interface (FFI)

To make the C++ engine accessible to other programming languages, Cactus uses a Foreign Function Interface (FFI). The FFI is a C-style API that wraps the C++ code and exposes it as a set of simple functions. This allows developers to use the C++ engine from languages like Dart (for Flutter) and JavaScript (for React Native) without having to write any C++ code themselves. The FFI is responsible for:

*   **Bridging the Gap:** The FFI acts as a bridge between the C++ world and the world of other programming languages. It handles the conversion of data types and memory management, so you don't have to worry about the low-level details.
*   **Platform Independence:** The FFI is designed to be platform-independent, so it can be used on a variety of operating systems, including iOS, Android, macOS, and Windows.

### 1.3. Flutter and React Native SDKs

To make it even easier to use Cactus in your mobile apps, the project provides SDKs for both Flutter and React Native. These SDKs provide a high-level, object-oriented API that wraps the FFI and makes it easy to use the C++ engine in your apps. The SDKs are responsible for:

*   **Simplified API:** The SDKs provide a simple and intuitive API that makes it easy to load models, run inference, and manage conversations.
*   **Platform Integration:** The SDKs handle the platform-specific details of integrating the C++ engine into your app, so you don't have to worry about the low-level details of building and packaging the C++ code.
*   **Example Apps:** The project also includes example apps for both Flutter and React Native that show you how to use the SDKs to build your own AI-powered apps.

### 1.4. How it All Works Together

Here's a high-level overview of how the different parts of the project work together:

1.  You start by adding the Cactus SDK to your Flutter or React Native project.
2.  You then use the SDK to download a GGUF-formatted model from Hugging Face or another source.
3.  The SDK calls the FFI to load the model into the C++ engine.
4.  You can then use the SDK to send prompts to the model and get back the generated text, embeddings, or other outputs.
5.  The SDK calls the FFI to run inference on the model, and the FFI calls the C++ engine to do the actual work.
6.  The C++ engine returns the results to the FFI, which returns them to the SDK, which returns them to your app.

This modular architecture makes Cactus a powerful and flexible framework for building AI-powered apps. You can use the C++ engine directly if you need maximum performance and control, or you can use the Flutter and React Native SDKs if you want to get up and running quickly.

## 2. Running a New GGUF Model

Here are the steps to download a GGUF model from Hugging Face and run it using the provided C++ example:

### 2.1. Find a GGUF Model on Hugging Face

The first step is to find a GGUF-formatted model on Hugging Face. Hugging Face is a popular platform for sharing and discovering AI models. You can browse the available models on the Hugging Face website:

[https://huggingface.co/models](https://huggingface.co/models)

When you're looking for a model, make sure to filter by the "GGUF" format. This will ensure that the model is compatible with the Cactus C++ engine. You can also filter by other criteria, such as the model size, the number of parameters, and the license.

For this example, we'll use the "gemma-2b-it-q4_k_m.gguf" model, which is a 4-bit quantized version of Google's Gemma 2B model. You can download the model from the following URL:

[https://huggingface.co/Meli/gemma-2b-it-q4_k_m-GGUF/resolve/main/gemma-2b-it-q4_k_m.gguf](https://huggingface.co/Meli/gemma-2b-it-q4_k_m-GGUF/resolve/main/gemma-2b-it-q4_k_m.gguf)

### 2.2. Download the Model

Once you've found a model you want to use, you can download it to your local machine. You can use the `wget` command to download the model from the command line.

```bash
wget https://huggingface.co/Meli/gemma-2b-it-q4_k_m-GGUF/resolve/main/gemma-2b-it-q4_k_m.gguf
```

This will download the model to your current directory. You can then move the model to a more convenient location, such as the `cpp/example` directory in the Cactus project.

### 2.3. Build and Run the C++ Example

Once you've downloaded the model, you can build and run the C++ example to test it. The C++ example is located in the `cpp/example` directory. To build the example, you'll need to have CMake and a C++ compiler installed on your system.

First, navigate to the `cpp/example` directory:

```bash
cd cpp/example
```

Next, run the `build.sh` script to build the example:

```bash
./build.sh
```

This will create an executable file called `cactus_llm` in the current directory. You can then run the example with the following command:

```bash
./cactus_llm -m gemma-2b-it-q4_k_m.gguf -p "Hello, who are you?"
```

This will load the model and run inference on the prompt "Hello, who are you?". The model will then generate a response, which will be printed to the console.

Here's an example of the output you might see:

```
Hello, who are you?
I am a large language model, trained by Google.
```

You can also run the example in interactive mode by using the `-i` flag:

```bash
./cactus_llm -m gemma-2b-it-q4_k_m.gguf -i
```

This will start an interactive chat session with the model. You can then type messages to the model and it will respond to you. To exit the interactive session, type `quit` or `exit`.

That's it! You've successfully downloaded a GGUF model from Hugging Face and run it using the provided C++ example. You can now experiment with other models and prompts to see what you can create.

## 3. Exposing the Model as a Web Server

Now, let's take the C++ example and turn it into a web server that exposes the model's inference capabilities through an API compatible with OpenAI's Chat Completion API. This will allow you to use the model from any programming language or tool that can make HTTP requests.

To create the web server, we'll use the `httplib.h` library, which is a simple and easy-to-use C++ library for creating HTTP servers and clients. We'll also use the `json.hpp` library, which is a popular C++ library for working with JSON.

### 3.1. Add the httplib.h and json.hpp Libraries to the Project

First, you'll need to add the `httplib.h` and `json.hpp` libraries to the project. You can download the latest versions of these libraries from the following URLs:

*   **httplib.h:** [https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h](https://raw.githubusercontent.com/yhirose/cpp-httplib/master/httplib.h)
*   **json.hpp:** [https://github.com/nlohmann/json/releases/latest/download/json.hpp](https://github.com/nlohmann/json/releases/latest/download/json.hpp)

Once you've downloaded the libraries, you'll need to add them to the `cpp/example` directory.

### 3.2. Create a New C++ File for the Web Server

Next, you'll need to create a new C++ file for the web server. You can call this file `main_server.cpp`. In this file, you'll need to include the `httplib.h` and `json.hpp` libraries, as well as the `cactus.h` library.

```cpp
#include "httplib.h"
#include "json.hpp"
#include "cactus.h"
```

### 3.3. Implement the Web Server

Now, you can implement the web server. The web server will have a single endpoint, `/v1/chat/completions`, which will be compatible with OpenAI's Chat Completion API. This endpoint will accept a POST request with a JSON body that contains the model, messages, and other parameters. The web server will then use the Cactus C++ engine to run inference on the model and return the generated text in the response.

Here's the code for the web server:

```cpp
#include "httplib.h"
#include "json.hpp"
#include "cactus.h"

using namespace httplib;
using json = nlohmann::json;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <model_path>" << std::endl;
        return 1;
    }

    std::string model_path = argv[1];

    cactus::cactus_context context;
    common_params params;
    params.model_path = model_path;
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

        json request_json = json::parse(req.body);

        std::string messages_str = request_json["messages"].dump();
        std::string formatted_prompt = context.getFormattedChat(messages_str, "");

        context.params.prompt = formatted_prompt;
        context.params.n_predict = request_json.value("max_tokens", 256);
        context.params.temp = request_json.value("temperature", 0.8);
        context.params.top_k = request_json.value("top_k", 40);
        context.params.top_p = request_json.value("top_p", 0.95);
        context.params.penalty_repeat = request_json.value("frequency_penalty", 1.1);
        context.params.mirostat = 0;
        context.params.ignore_eos = false;

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

    std::cout << "Server listening on port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);

    return 0;
}
```

### 3.4. Build and Run the Web Server

Once you've created the web server, you can build and run it. To build the web server, you'll need to modify the `CMakeLists.txt` file in the `cpp/example` directory to include the new `main_server.cpp` file.

```cmake
add_executable(cactus_server main_server.cpp)
target_link_libraries(cactus_server PRIVATE cactus_core_lib)
```

You can then build the web server by running the `build.sh` script:

```bash
./build.sh
```

This will create an executable file called `cactus_server` in the current directory. You can then run the web server with the following command:

```bash
./cactus_server gemma-2b-it-q4_k_m.gguf
```

This will start the web server and it will listen for requests on port 8080.

### 3.5. Test the Web Server

Once the web server is running, you can test it by sending a POST request to the `/v1/chat/completions` endpoint. You can use the `curl` command to send the request from the command line.

```bash
curl -X POST http://localhost:8080/v1/chat/completions -H "Content-Type: application/json" -d '{
    "model": "gemma-2b-it",
    "messages": [
        {"role": "user", "content": "Hello, who are you?"}
    ]
}'
```

The web server will then run inference on the model and return the generated text in the response. Here's an example of the response you might see:

```json
{
    "choices": [
        {
            "message": {
                "role": "assistant",
                "content": "I am a large language model, trained by Google."
            }
        }
    ]
}
```

That's it! You've successfully created a web server that exposes the model's inference capabilities through an API compatible with OpenAI's Chat Completion API. You can now use the model from any programming language or tool that can make HTTP requests.

## 4. Whisper API for Speech-to-Text

To create a voice-enabled chat interface, you'll need to integrate a speech-to-text model, like Whisper, into your application. Whisper is an open-source speech recognition model from OpenAI that is known for its high accuracy.

The Cactus project doesn't have built-in support for Whisper, but you can easily integrate it into your application by using the `whisper.cpp` library, which is a C++ port of the Whisper model. `whisper.cpp` is designed to be efficient and easy to use, and it can be run on a variety of hardware, from smartphones to servers.

Here's how you can integrate Whisper into your application:

### 4.1. Add the whisper.cpp Library to Your Project

First, you'll need to add the `whisper.cpp` library to your project. You can clone the `whisper.cpp` repository from GitHub:

```bash
git clone https://github.com/ggerganov/whisper.cpp.git
```

Once you've cloned the repository, you'll need to add the `whisper.cpp` source files to your project. You can do this by adding the following line to your `CMakeLists.txt` file:

```cmake
add_subdirectory(whisper.cpp)
```

### 4.2. Implement the Speech-to-Text Logic

Next, you'll need to implement the speech-to-text logic in your application. This will involve the following steps:

1.  **Load the Whisper model:** You'll need to load the Whisper model into memory. You can do this by using the `whisper_init_from_file` function.
2.  **Record audio from the microphone:** You'll need to record audio from the microphone. You can use a library like `SDL` or `PortAudio` to do this.
3.  **Run inference on the Whisper model:** You'll need to run inference on the Whisper model to transcribe the audio to text. You can do this by using the `whisper_full` function.
4.  **Get the transcribed text:** You'll need to get the transcribed text from the Whisper model. You can do this by using the `whisper_full_get_segment_text` function.

Here's an example of how you can implement the speech-to-text logic in your application:

```cpp
#include "whisper.h"

// ...

struct whisper_context * ctx = whisper_init_from_file("path/to/ggml-base.en.bin");

// ...

std::vector<float> pcmf32; // audio data from microphone

whisper_full_params wparams = whisper_full_default_params(WHISPER_SAMPLING_GREEDY);

if (whisper_full(ctx, wparams, pcmf32.data(), pcmf32.size()) != 0) {
    fprintf(stderr, "failed to process audio\n");
    return 7;
}

const int n_segments = whisper_full_n_segments(ctx);
for (int i = 0; i < n_segments; ++i) {
    const char * text = whisper_full_get_segment_text(ctx, i);
    printf("%s", text);
}

// ...

whisper_free(ctx);
```

### 4.3. Integrate the Speech-to-Text Logic into Your Web Server

Once you've implemented the speech-to-text logic, you can integrate it into your web server. This will allow you to create a voice-enabled chat interface where users can speak to the model and get a response.

To do this, you'll need to add a new endpoint to your web server that accepts audio data. This endpoint will then use the Whisper model to transcribe the audio to text, and then it will use the Cactus C++ engine to run inference on the transcribed text. The web server will then return the generated text in the response.

Here's an example of how you can add a new endpoint to your web server for speech-to-text:

```cpp
svr.Post("/v1/audio/transcriptions", [&](const Request& req, Response& res) {
    // ...

    std::vector<float> pcmf32; // audio data from request

    // ...

    if (whisper_full(ctx, wparams, pcmf32.data(), pcmf32.size()) != 0) {
        fprintf(stderr, "failed to process audio\n");
        res.status = 500;
        return;
    }

    std::string transcribed_text;
    const int n_segments = whisper_full_n_segments(ctx);
    for (int i = 0; i < n_segments; ++i) {
        const char * text = whisper_full_get_segment_text(ctx, i);
        transcribed_text += text;
    }

    // ... run inference on transcribed_text ...

    res.set_content(response_json.dump(), "application/json");
});
```

By integrating Whisper into your application, you can create a powerful and intuitive voice-enabled chat interface that allows users to interact with your model in a natural way.

## 5. Multi-modal Models

The Cactus project has built-in support for multi-modal models like LLaVA, which can process both text and images. This allows you to build applications that can "see" and understand the world around them.

To use a multi-modal model with the Cactus project, you'll need to do the following:

### 5.1. Download a Multi-modal Model

First, you'll need to download a multi-modal model in GGUF format. You can find multi-modal models on Hugging Face by filtering by the "GGUF" format and the "image-text-to-text" tag.

For this example, we'll use the "llava-v1.5-7b-q4.gguf" model, which is a 4-bit quantized version of the LLaVA 1.5 7B model. You can download the model from the following URL:

[https://huggingface.co/mys/ggml_llava-v1.5-7b/resolve/main/ggml-model-q4_k.gguf](https://huggingface.co/mys/ggml_llava-v1.5-7b/resolve/main/ggml-model-q4_k.gguf)

You'll also need to download the `mmproj` file, which contains the vision projection weights. You can download the `mmproj` file from the following URL:

[https://huggingface.co/mys/ggml_llava-v1.5-7b/resolve/main/mmproj-model-f16.gguf](https://huggingface.co/mys/ggml_llava-v1.5-7b/resolve/main/mmproj-model-f16.gguf)

### 5.2. Modify the C++ Example to Use the Multi-modal Model

Next, you'll need to modify the C++ example to use the multi-modal model. You'll need to make the following changes to the `main_vlm.cpp` file in the `cpp/example` directory:

*   **Load the multi-modal model:** You'll need to load the multi-modal model and the `mmproj` file. You can do this by using the `initMultimodal` function.
*   **Load the image:** You'll need to load the image that you want to process. You can do this by using the `processMedia` function.
*   **Run inference on the model:** You'll need to run inference on the model with the image and the text prompt.

Here's an example of how you can modify the `main_vlm.cpp` file to use the multi-modal model:

```cpp
#include "cactus.h"
#include "utils.h"

int main(int argc, char **argv) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <model_path> <mmproj_path> <image_path>\n", argv[0]);
        return 1;
    }

    std::string model_path = argv[1];
    std::string mmproj_path = argv[2];
    std::string image_path = argv[3];

    cactus::cactus_context context;
    common_params params;
    params.model_path = model_path;

    if (!context.loadModel(params)) {
        return 1;
    }

    if (!context.initMultimodal(mmproj_path, true)) {
        return 1;
    }

    std::string prompt = "Describe the image.";
    std::vector<std::string> media_paths = {image_path};

    context.params.prompt = prompt;
    context.loadPrompt(media_paths);

    while (context.has_next_token && !context.is_interrupted) {
        auto token = context.doCompletion();
        if (token.tok == -1) break;
        std::cout << context.generated_text.substr(context.generated_text.length() - 1);
        fflush(stdout);
    }

    std::cout << std::endl;

    return 0;
}
```

### 5.3. Build and Run the C++ Example

Once you've modified the C++ example, you can build and run it. To build the example, you'll need to run the `build.sh` script:

```bash
./build.sh
```

This will create an executable file called `cactus_vlm` in the current directory. You can then run the example with the following command:

```bash
./cactus_vlm llava-v1.5-7b-q4.gguf mmproj-model-f16.gguf image.jpg
```

This will load the multi-modal model and the image, and then it will run inference on the model with the prompt "Describe the image.". The model will then generate a description of the image, which will be printed to the console.

By using multi-modal models with the Cactus project, you can build powerful applications that can understand and interact with the world in a more natural way.

## 6. Gemma Models

I was unable to find any information about a model named "gemma3n". It's possible that this is a new model that has not been released yet, or it may be a typo.

If you have a link to the model on Hugging Face or another source, I would be happy to take a look and see if I can find more information about it. In the meantime, I can tell you about the Gemma family of models from Google.

### The Gemma Family of Models

Gemma is a family of lightweight, state-of-the-art open models from Google. They are built from the same research and technology used to create the Gemini models. Gemma models are well-suited for a variety of text generation tasks, including question answering, summarization, and dialogue.

There are two sizes of Gemma models:

*   **Gemma 2B:** This is a 2-billion parameter model that is designed for high performance and efficiency. It can be run on a variety of hardware, from smartphones to servers.
*   **Gemma 7B:** This is a 7-billion parameter model that is designed for high quality and accuracy. It is well-suited for tasks that require a deep understanding of language.

Both Gemma 2B and Gemma 7B are available in GGUF format, so you can use them with the Cactus project. You can find the Gemma models on Hugging Face by searching for "gemma".

### How to Use Gemma with the Cactus Project

To use a Gemma model with the Cactus project, you'll need to do the following:

1.  **Download a Gemma model:** You can download a Gemma model in GGUF format from Hugging Face.
2.  **Build and run the C++ example:** You can use the C++ example to run inference on the Gemma model.

For example, to use the Gemma 2B model, you would download the "gemma-2b-it-q4_k_m.gguf" model from Hugging Face and then run the C++ example with the following command:

```bash
./cactus_llm -m gemma-2b-it-q4_k_m.gguf -p "Hello, who are you?"
```

This will load the Gemma 2B model and run inference on the prompt "Hello, who are you?". The model will then generate a response, which will be printed to the console.

I hope this information is helpful. If you have any other questions, please let me know.
