#include <iostream>
#include <assert.h>
#include "logger.h"

void basicTest() {
    Logger logger(true);
    logger << "Test\n";
    assert(logger.getTotalBuffer() == "Test\n");
}

void multipleLinesTest() {
    Logger logger(true);
    logger << "Line1\n";
    logger << "Line2\n";
    assert(logger.getTotalBuffer() == "Line1\nLine2\n");
}

void indentTest() {
    Logger logger(true);
    logger << "Line1\n";
    LoggerIndent indent(logger);
    logger << "Line2\n";
    assert(logger.getTotalBuffer() == "Line1\n|   Line2\n");
}

void indent2Test() {
    Logger logger(true);
    logger << "Line1\n";
    {
        LoggerIndent indent(logger);
        logger << "Line2\n";
    }
    logger << "Line3\n";
    assert(logger.getTotalBuffer() == "Line1\n|   Line2\nLine3\n");
}

void indent3Test() {
    Logger logger(true);
    logger << "Line1\n";
    LoggerIndent indent1(logger);
    logger << "Line2\n";
    LoggerIndent indent2(logger);
    logger << "Line3\n";
    assert(logger.getTotalBuffer() == "Line1\n|   Line2\n|   |   Line3\n");
}

void loggerFlushTest() {
    Logger logger(true);
    logger << "Str1";
    assert(logger.getLineBuffer() == "Str1");
    assert(logger.getTotalBuffer() == "");
    logger << LoggerFlush();
    assert(logger.getLineBuffer() == "");
    assert(logger.getTotalBuffer() == "Str1");
    logger << "Str2";
    assert(logger.getLineBuffer() == "Str2");
    assert(logger.getTotalBuffer() == "Str1");
    logger << LoggerFlush();
    assert(logger.getLineBuffer() == "");
    assert(logger.getTotalBuffer() == "Str1Str2");
    logger << "\n";
    logger << "Str3\n";
    assert(logger.getTotalBuffer() == "Str1Str2\nStr3\n");
}

void onlineWriteTest() {
    Logger logger(true);
    std::string str;
    logger.OnLineWrite = [&](std::string line) {
        str = line;
    };
    logger << "Line1\n";
    assert(str == "Line1");
    logger << "Str1";
    assert(str == "Line1");
    logger << LoggerFlush();
    assert(str == "Str1");
    logger << "Str2";
    assert(str == "Str1");
    logger << "\n";
    assert(str == "Str2");
}

void tagTest() {
    Logger logger(true);
    LoggerTag tag1(logger, "tag1");
    logger << "tag1\n";
    assert(logger.getTotalBuffer() == "tag1\n");
}

void deactivateTest() {
    Logger logger(true);
    LoggerDeactivate deact(logger);
    LoggerTag tag1(logger, "tag1");
    logger << "tag1\n";
    assert(logger.getTotalBuffer() == "");
}

void enableTagTest() {
    Logger logger(true);
    LoggerDeactivate deact(logger);
    LoggerEnableTag enable_tag1(logger, "tag1");
    LoggerEnableTag enable_someTag(logger, "someTag");
    LoggerDisableTag disable_someOtherTag(logger, "someOtherTag");
    {
        LoggerTag tag1(logger, "tag1");
        logger << "tag1\n";
    }
    {
        LoggerTag tag2(logger, "tag2");
        logger << "tag2\n";
    }
    assert(logger.getTotalBuffer() == "tag1\n");
}

void disableTagTest() {
    Logger logger(true);
    LoggerDisableTag disable_tag2(logger, "tag2");
    LoggerEnableTag enable_someTag(logger, "someTag");
    LoggerDisableTag disable_someOtherTag(logger, "someOtherTag");
    {
        LoggerTag tag1(logger, "tag1");
        logger << "tag1\n";
    }
    {
        LoggerTag tag2(logger, "tag2");
        logger << "tag2\n";
    }
    assert(logger.getTotalBuffer() == "tag1\n");
}

void returnDisabledTest() {
    Logger logger(true);
    LoggerDisableTag disable_tag1(logger, "tag1");
    LoggerTag tag1(logger, "tag1");
    logger << "tag1 first\n";
    {
        LoggerTag tag2(logger, "tag2");
        logger << "tag2\n";
    }
    logger << "tag1 second\n";
    assert(logger.getTotalBuffer() == "tag2\n");
}

void nestedTags1Test() {
    Logger logger(true);
    LoggerDeactivate deact(logger);
    LoggerEnableTag enable_tag1(logger, "tag1");
    LoggerEnableTag enable_tag3(logger, "tag3");
    {
        LoggerTag tag1(logger, "tag1");
        logger << "tag1\n";
        {
            LoggerTag tag2(logger, "tag2");
            logger << "tag2\n";
            {
                LoggerTag tag3(logger, "tag3");
                logger << "tag3\n";
            }
        }
    }
    assert(logger.getTotalBuffer() == "tag1\ntag3\n");
}

void reenableTag1Test() {
    Logger logger(true);
    {
        LoggerTag tag1(logger, "tag1");
        logger << "tag1\n";
        {
            LoggerDisableTag disable_tag2(logger, "tag2");
            LoggerTag tag2(logger, "tag2");
            logger << "tag2 first\n";
        }
        {
            LoggerTag tag2(logger, "tag2");
            logger << "tag2 second\n";
        }
    }
    assert(logger.getTotalBuffer() == "tag1\ntag2 second\n");
}

void disableAfterTagTest() {
    Logger logger(true);
    {
        LoggerTag tag1(logger, "tag1");
        logger << "tag1 first\n";
        LoggerDisableTag disable_tag1(logger, "tag1");
        logger << "tag1 second\n";
        {
            LoggerTag tag2(logger, "tag2");
            logger << "tag2\n";
        }
        logger << "tag1 third\n";
    }
    assert(logger.getTotalBuffer() == "tag1 first\ntag2\n");
}

void reenableTag2Test() {
    Logger logger(true);
    {
        {
            LoggerTag tag1(logger, "tag1");
            {
                LoggerDisableTag disable_tag1(logger, "tag1");
                LoggerTag tag2(logger, "tag2");
            }
            logger << "tag1 first\n";
        }
        {
            LoggerTag tag1(logger, "tag1");
            {
                LoggerTag tag2(logger, "tag2");
                LoggerDisableTag disable_tag1(logger, "tag1");
            }
            logger << "tag1 second\n";
        }
    }
    assert(logger.getTotalBuffer() == "tag1 first\ntag1 second\n");
}

void nestedTags2Test() {
    Logger logger(true);
    LoggerTag tag1(logger, "tag1");
    LoggerDisableTag disable_tag2(logger, "tag2");
    logger << "tag1 first\n";
    {
        LoggerTag tag2(logger, "tag2");
        logger << "tag2 1\n";
        {
            LoggerTag tag3(logger, "tag3");
            logger << "tag3 1\n";
            {
                LoggerTag tag2(logger, "tag2");
                logger << "tag2 2\n";
                {
                    LoggerTag tag4(logger, "tag4");
                    logger << "tag4 1\n";
                    {
                        LoggerTag tag1_again(logger, "tag1");
                        logger << "tag1 second\n";
                    }
                    logger << "tag4 2\n";
                }
                logger << "tag2 3\n";
            }
            logger << "tag3 2\n";
        }
        logger << "tag2 4\n";
    }
    logger << "tag1 third\n";
    assert(logger.getTotalBuffer() ==
        "tag1 first\n"
        "tag3 1\n"
        "tag4 1\n"
        "tag1 second\n"
        "tag4 2\n"
        "tag3 2\n"
        "tag1 third\n"
    );
}

int main() {
    // Logger::disableStdWrite();
    basicTest();
    multipleLinesTest();
    indentTest();
    indent2Test();
    indent3Test();
    loggerFlushTest();
    onlineWriteTest();
    tagTest();
    deactivateTest();
    enableTagTest();
    disableTagTest();
    returnDisabledTest();
    nestedTags1Test();
    reenableTag1Test();
    disableAfterTagTest();
    reenableTag2Test();
    nestedTags2Test();
    // Logger::enableStdWrite();
    std::cout << std::endl;
    std::cout << "ALL PASSED" << std::endl;
    return 0;
}
