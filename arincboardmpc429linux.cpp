#include "arincboardmpc429linux.h"


ArincBoardMPC429::ArincBoardMPC429(const char *boardname, int MAX_NUMBER_CHANNEL)
{

}

void ArincBoardMPC429::stopBoard()
{

}

void ArincBoardMPC429::closeBoard()
{

}

ArincBoardMPC429::~ArincBoardMPC429()
{
    delete name;
}

int ArincChannelMPC429::count=0;

ArincChannelMPC429::ArincChannelMPC429(ArincBoardMPC429 *board, int number_channel, int number_bank)
{
    ++count;
}

unsigned int *ArincChannelMPC429::readBuffer()
{

}

void ArincChannelMPC429::Start()
{

}

void ArincChannelMPC429::Stop()
{

}

int ArincChannelMPC429::sizeOfBuffer() const
{

}
