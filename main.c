#include "stomptalk/parser.h"
#include <string.h>
#include <stdio.h>

int at_frame(struct stomptalk_parser* parser, const char* at);

int at_method(struct stomptalk_parser* parser, const char *at, size_t length);

int at_hdr_key(struct stomptalk_parser* parser, const char *at, size_t length);

int at_hdr_val(struct stomptalk_parser* parser, const char *at, size_t length);

int at_body(struct stomptalk_parser* parser, const char *at, size_t length);

int at_frame_end(struct stomptalk_parser* parser, const char*);

size_t connected_count = 0;
size_t frame_count = 0;

int main()
{
    const char example10[] =
        "CONNECTED\r\n"
            "version:1.2\r\n"
            "session:STOMP-PARSER-TEST\r\n"
            "server:stomp-parser/1.0.0\r\n"
            "\r\n\0"
        "SEND\n"
            "id:0\n"
            "destination:/queue/foo\n"
            "ack:client\n"
            "\n\0"
        "SEND\r\n"
            "id:0\r\n"
            "\r\n\0"
        "SEND\r\n"
            "id:0\r\n"
            "\r\n\0"
        "SEND\n"
            "subscription:0\n"
            "message-id:007\n"
            "destination:/queue/a\n"
            "content-length:13\n"
            "content-type:text/plain\n"
            "message-error:false\n"
            "\n"
            "hello queue a\0"
        "SEND\r\n"
            "subscription:0\r\n"
            "message-id:007\r\n"
            "destination:/queue/a\r\n"
            "content-type:application/json\r\n"
            "message-no-content-length:true\r\n"
            "\r\n"
            "[1,2,3,4,5,6,7]\0"
        "SEND\r\n"
            "subscription:0\r\n"
            "message-id:007\r\n"
            "destination:/queue/a\r\n"
            "content-length:13\r\n"
            "content-type:text/plain\r\n"
            "message-error:false\r\n"
            "\r\n"
            "hello queue a\0"
        "SEND\r\n"
            "subscription:0\r\n"
            "message-id:007\r\n"
            "destination:/queue/a\r\n"
            "content-length:13\r\n"
            "message-error:false\r\n"
            "\r\n"
            "hello queue a\0"
        "SEND\r\n"
            "subscription:0\r\n"
            "message-id:007\r\n"
            "destination:/queue/a\r\n"
            "\r\n"
            "hello queue a\0"
        "SEND\r\n"
            "receipt:77\r\n"
            "\r\n\0";

    stomptalk_parser_hook hook = {
        .on_frame = &at_frame,
        .on_method = &at_method,
        .on_hdr_key = &at_hdr_key,
        .on_hdr_val = &at_hdr_val,
        .on_frame_end = &at_frame_end
    };

    stomptalk_parser *parser = stomptalk_parser_new();

    // 100 million of frames
    // on my pc it takes about 17 seconds
    // ./purestomp  16,72s user 0,00s system 99% cpu 16,740 total

    size_t count = 10000000;
    for (size_t i = 0; i < count; ++i)
    {
        size_t needle = 0;
        const char *data = example10;
        size_t size = sizeof(example10) - 1;
        const char *data_end = data + size;
        size_t chunk_size = size;

        while (data != data_end)
        {
            // сколько буфера осталось
            needle = data_end - data;
            // по сколько бдуем читать
            //chunk_size = rand() % (size / 5);
            size_t readsize = chunk_size < needle ? chunk_size :needle;
            // парсим
            size_t rc = stomptalk_parser_execute(parser, &hook, data, readsize);
            if (rc != readsize)
            {
                // it's error!
                stomptalk_parser_free(parser);
                return 1;
            }

            data += rc;

            // проверяем все ли пропарсили
            if (needle == rc)
            {
                // this is end
                break;
            }
        }
    }

    fprintf(stdout, "connected %zu, frame %zu\n", connected_count, frame_count);

    stomptalk_parser_free(parser);
    return 0;
}

int at_frame(struct stomptalk_parser* parser, const char* at)
{
    // no error
    return 0;
}

int at_method(struct stomptalk_parser* parser, const char* at, size_t length)
{
//    // detect method using memcmp
//    static const char connected_method[] = "CONNECTED";
//    static const size_t connected_method_size = sizeof(connected_method) - 1;
//    if (length == connected_method_size)
//    {
//        if (memcmp(at, connected_method, length) == 0)
//            ++connected_count;
//    }

    // or detect using stomptalk_eval_method
    if (stomtalk_connected == stomptalk_eval_method(at, length))
        ++connected_count;

    return 0;
}

int at_hdr_key(struct stomptalk_parser* parser, const char* at, size_t length)
{
    return 0;
}

int at_hdr_val(struct stomptalk_parser* parser, const char* at, size_t length)
{
    return 0;
}

int at_body(struct stomptalk_parser* parser, const char* at, size_t length)
{
    return 0;
}

int at_frame_end(struct stomptalk_parser* parser, const char* at)
{
    ++frame_count;
    // no error
    return 0;
}
