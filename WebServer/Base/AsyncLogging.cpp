/*  Version:1.0 
    Author:LuoQiYu
    Date:2023-06-27 */

#include "AsyncLogging.h"
#include <vector>
#include <assert.h>

void AsynecLogging::threadFunc(){
    assert(running_ == true);
    latch_.countDown();
    LogFile output(basename_);
    BufferPtr newBuffer1(new Buffer);
    BufferPtr newBUffer2(new Buffer);
    newBuffer1->bzero();
    newBuffer2->bzero();
    BufferVector buffersToWrite;        //Belong to Background, translate with Front
    buffersToWrite.reserve(16);

    while (running_)
    {
        assert(newBuffer1 && newBuffer1->length() == 0);
        assert(newBuffer2 && newBuffer2->length() == 0);
        assert(buffersToWrite.empty());

        {
            MutexLockGuard lock(mutex_);
            //Two ways, 3 seconds or currentBuffer is full
            if (buffers_.empty())
            {
                cond_.waitForSeconds(flushInterval_);
            }
            buffers_.push_back(std::move(currentBuffer_));
            currentBuffer_ = std::move(newBuffer1);

            buffersToWrite.swap(buffers_);
            if(!nextBuffer_)
                nextBuffer_ = std::move(newBuffer2);
        }

        assert(!buffersToWrite.empty());

        if (buffersToWrite.size() > 25){
            //Only leave two origin buffer and delete the others
            buffersToWrite.erase(buffersToWrite.begin() + 2, buffersToWrite.end());
        }

        for (const auto& buffer: buffersToWrite){
            output.append(buffer->data(), buffer->length());
        }

        // Modify the size of buffersToWrite to two original buffer
        if (buffersToWrite.size() > 2){
            buffersToWrite.resize(2);
        }

        if (!newBuffer1){
            assert(!buffersToWrite.empty());
            newBuffer1 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer1->reset();
        }

        if (!newBuffer2){
            assert(!buffersToWrite.empty());
            newBuffer2 = buffersToWrite.back();
            buffersToWrite.pop_back();
            newBuffer2->reset();
        }

        buffersToWrite.clear();
        output.flush();
    }
    output.flush();
}