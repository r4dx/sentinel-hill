#include "web/WebRequest.h"

#ifdef UNIT_TEST
#include <TestHandler.h>
#include <unity.h>

TestHandler handler;
WebRequest mockRequest("");

void testGetPath(void) {
    TEST_ASSERT_TRUE("Test" == handler.getPath());
}

void testPost(void) {
    WebResponse response = handler.post(mockRequest);
    TEST_ASSERT_TRUE("<html><h1>POST</h1></html>" == response.getResponse());
}

void process() {
    UNITY_BEGIN();
    RUN_TEST(testGetPath);
    RUN_TEST(testPost);
    UNITY_END();
}

int main(int argc, char **argv) {
    process();
    return 0;
}
#endif