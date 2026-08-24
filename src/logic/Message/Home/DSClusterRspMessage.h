#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class DSClusterRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        PiranhaMessage::Encode();
        
        ByteStreamHelper::WriteBlockTag(*_stream, 1, 192, 4246);

        _stream->WriteVInt(3);

        int s0 = _stream->GetOffset();
        {   
            // first element
            _stream->WriteBoolean(true);

            ByteStreamHelper::WriteTaggedString(*_stream, 1, "alligator");
            ByteStreamHelper::WriteBlockTag(*_stream, 2, 192, 1031);

            int s1 = _stream->GetOffset();
            _stream->WriteVInt(23);
            {
                _stream->WriteString("ec2-34-228-170-216.compute-1.amazonaws.com");
                _stream->WriteString("ec2-184-73-151-37.compute-1.amazonaws.com");
                _stream->WriteString("ec2-54-221-171-70.compute-1.amazonaws.com");
                _stream->WriteString("ec2-3-91-78-6.compute-1.amazonaws.com");
                _stream->WriteString("ec2-54-90-147-152.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-193-24-25.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-202-78-39.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-206-230-190.compute-1.amazonaws.com");
                _stream->WriteString("ec2-3-237-80-171.compute-1.amazonaws.com");
                _stream->WriteString("ec2-52-201-243-119.compute-1.amazonaws.com");
                _stream->WriteString("ec2-184-72-120-165.compute-1.amazonaws.com");
                _stream->WriteString("ec2-98-93-215-108.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-196-47-57.compute-1.amazonaws.com");
                _stream->WriteString("ec2-100-53-226-22.compute-1.amazonaws.com");
                _stream->WriteString("ec2-3-232-96-49.compute-1.amazonaws.com");
                _stream->WriteString("ec2-18-234-241-165.compute-1.amazonaws.com");
                _stream->WriteString("ec2-13-222-223-8.compute-1.amazonaws.com");
                _stream->WriteString("ec2-100-26-43-220.compute-1.amazonaws.com");
                _stream->WriteString("ec2-107-22-44-159.compute-1.amazonaws.com");
                _stream->WriteString("ec2-98-81-243-72.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-211-231-131.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-203-151-244.compute-1.amazonaws.com");
                _stream->WriteString("ec2-44-195-25-160.compute-1.amazonaws.com");
            }
            int e1 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s1 - e1, s1 - 4);

            // second element
            _stream->WriteBoolean(true);

            ByteStreamHelper::WriteTaggedString(*_stream, 1, "cheetah");
            ByteStreamHelper::WriteBlockTag(*_stream, 2, 192, 1546);

            s1 = _stream->GetOffset();
            {
                _stream->WriteVInt(30);
                _stream->WriteString("ec2-34-217-88-194.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-213-184-60.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-160-82-233.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-16-144-247-11.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-220-196-173.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-32-186-131-253.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-87-150-251.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-90-185-175.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-94-113-154.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-162-60-197.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-211-120-254.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-90-112-79.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-35-160-182-172.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-52-10-230-171.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-54-186-134-71.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-18-237-167-253.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-44-249-92-110.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-16-148-1-144.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-44-242-220-61.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-54-244-30-121.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-208-150-88.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-222-103-128.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-18-237-83-222.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-54-218-155-119.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-209-72-152.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-34-208-225-187.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-52-34-90-19.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-18-236-75-99.us-west-2.compute.amazonaws.com");
                _stream->WriteString("ec2-44-246-195-208.us-west-2.compute.amazonaws.com");
                _stream->WriteString("");
            }
            e1 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s1 - e1, s1 - 4);

            // third element
            _stream->WriteBoolean(true);

            ByteStreamHelper::WriteTaggedString(*_stream, 1, "bear");
            ByteStreamHelper::WriteBlockTag(*_stream, 2, 192, 1606);

            s1 = _stream->GetOffset();
            {
                _stream->WriteVInt(30);
                _stream->WriteString("ec2-52-58-140-0.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-176-97-137.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-180-68-107.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-179-0-154.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-18-192-106-116.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-68-70-97.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-18-185-84-135.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-18-159-97-247.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-52-59-227-96.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-125-123-178.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-69-148-83.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-68-106-175.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-35-159-11-146.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-35-158-75-98.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-35-159-108-30.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-79-193-178.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-178-45-170.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-35-158-121-101.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-127-81-145.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-178-122-77.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-65-1-187.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-67-77-66.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-123-22-15.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-3-64-11-93.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-63-178-72-180.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-18-153-69-107.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-18-192-55-119.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("ec2-51-102-69-56.eu-central-1.compute.amazonaws.com");
                _stream->WriteString("");
                _stream->WriteString("ec2-18-184-18-229.eu-central-1.compute.amazonaws.com");
            }
            e1 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s1 - e1, s1 - 4);

        }
        int e0 = _stream->GetOffset();
        _stream->WriteIntBigEndianAt(s0 - e0, s0 - 4);
        
        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 21732;
    }
};