#include "fix_inverted_MFBO.h"
#include "adt.h"
#include "logger.h"

#include <sstream>

int FixInvertedMFBO::Work(int argc, char* argv[])
{
    //Init
    std::string targetADTFilename = argv[2];

    std::unique_ptr<std::fstream> targetFile;
    std::unique_ptr<adt> targetADT;
    std::tie(targetFile, targetADT) = OpenAdtFile(targetADTFilename);

    if (!targetFile)
        return 1;

    //Fix the bug if needed
    if (targetADT->mfbo)
    {
        if (targetADT->mfbo->hasInvertedMinMax())
        {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s has inverted coordinates, fixing it.", targetADTFilename.c_str());
            targetADT->mfbo->invertMinMax();

            targetADT->WriteToDisk(*targetFile);
        }
        else {
            sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s seems already correct, nothing to do.", targetADTFilename.c_str());
        }
    }
    else {
        sLogger->Out(Logger::LogLevel::LOG_LEVEL_NORMAL, "%s has no MFBO data, nothing to do.", targetADTFilename.c_str());
    }

    return 0;
}