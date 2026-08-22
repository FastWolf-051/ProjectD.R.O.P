#pragma once

#include "../../../titan/Message/PiranhaMessage.h"

class HomePlayerDataRspMessage : public PiranhaMessage {
public:
    void Encode() override {
        _stream->WriteVInt(5);
        _stream->WriteVInt(0);
        _stream->WriteVInt(9);
        {
            _stream->WriteString("client.account_id");
            _stream->WriteString("15633");

            _stream->WriteString("client.country");
            _stream->WriteString("UA");

            _stream->WriteString("client.device");
            _stream->WriteString("ANDROID_DEVICE");

            _stream->WriteString("client.device_id");
            _stream->WriteString("JVCmbb6v");

            _stream->WriteString("client.ip");
            _stream->WriteString("111.111.111.11");

            _stream->WriteString("client.version");
            _stream->WriteString("0.3.296710");

            _stream->WriteString("sampled");
            _stream->WriteString("false");

            _stream->WriteString("span-id");
            _stream->WriteString("a8804d60065998fb");

            _stream->WriteString("trace-id");
            _stream->WriteString("6a8500ed00b6d569665d3f3429865681d7ac0");
        }

        _stream->WriteVInt(1);
        _stream->WriteByte(160);
        _stream->WriteInt(1398);

        int s0 = _stream->GetOffset();
        _stream->WriteBoolean(true);
        {
            _stream->WriteTaggedVInt(1001, 1);
            _stream->WriteTaggedVInt(200, 2);
            _stream->WriteTaggedVInt(1002, 3);
            _stream->WriteTaggedVInt(107000031, 4);
            _stream->WriteTaggedVInt(1003, 5);
            _stream->WriteTaggedVInt(1004, 6);
            _stream->WriteTaggedVInt(1005, 7);
            _stream->WriteTaggedVInt(1006, 8);
            _stream->WriteTaggedVInt(1007, 9);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 10, 160, 11);
            
            int s1 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                _stream->WriteTaggedVInt(0, 1);
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(5, 3);
                _stream->WriteVInt(-1);
            }
            int e1 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s1 - e1, s1 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 12, 192, 11);

            int s2 = _stream->GetOffset();
            _stream->WriteVInt(0);

            int e2 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s2 - e2, s2 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 13, 160, 32);
            
            int s3 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                ByteStreamHelper::WriteTaggedString(*_stream, 1, "INACTIVE");

                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(0, 3);

                ByteStreamHelper::WriteBlockTag(*_stream, 4, 192, 1);

                int s4 = _stream->GetOffset();
                _stream->WriteVInt(0);
                int e4 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s4 - e4, s4 - 4);
                
                _stream->WriteTaggedVInt(0, 5);
                _stream->WriteVInt(-1);
            }
            int e3 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s3 - e3, s3 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 14, 160, 8);

            int s5 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                _stream->WriteTaggedVInt(0, 1);
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteVInt(-1);
            }
            int e5 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s5 - e5, s5 - 4);

            ByteStreamHelper::WriteTaggedBoolean(*_stream, 15, false);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 16, 192, 122);

            int s6 = _stream->GetOffset();
            _stream->WriteVInt(8); // resources array
            {   
                // gold
                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(101, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(90, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(103, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(91, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(104, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(92, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(107, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(93, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(105, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(94, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                // karma coin
                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(112, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(95, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(113, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(96, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);

                // hero shard
                _stream->WriteBoolean(true);
                _stream->WriteTaggedVInt(115, 1); // resource id
                _stream->WriteTaggedVInt(0, 2);
                _stream->WriteTaggedVInt(97, 3); // value
                _stream->WriteTaggedVInt(0, 4);
                _stream->WriteVInt(-1);   
            }
            int e6 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s6 - e6, s6 - 4);
            
            ByteStreamHelper::WriteTaggedString(*_stream, 17, "alligator");

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 21, 160, 9);
            
            int s7 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                _stream->WriteInt(0);
                _stream->WriteInt(15633);
            }
            int e7 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s7 - e7, s7 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 24, 192, 1);

            int s8 = _stream->GetOffset();
            _stream->WriteVInt(0);
            int e8 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s8 - e8, s8 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 25, 160, 31);

            int s9 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                ByteStreamHelper::WriteTaggedString(*_stream, 1, "(null)");
                ByteStreamHelper::WriteBlockTag(*_stream, 2, 192, 1);

                int s10 = _stream->GetOffset();
                _stream->WriteVInt(0);
                int e10 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s10 - e10, s10 - 4);

                _stream->WriteTaggedVInt(0, 4);

                ByteStreamHelper::WriteBlockTag(*_stream, 6, 160, 1);

                int s11 = _stream->GetOffset();
                _stream->WriteBoolean(false);
                int e11 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s11 - e11, s11 - 4);

                _stream->WriteTaggedVInt(0, 7);
                _stream->WriteTaggedVInt(0, 8);
                _stream->WriteVInt(-1);
            }  
            int e9 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s9 - e9, s9 - 4);

            // stub
            ByteStreamHelper::WriteBlockTag(*_stream, 26, 160, 41);
            
            int s12 = _stream->GetOffset();
            _stream->WriteBoolean(true);
            {
                ByteStreamHelper::WriteBlockTag(*_stream, 1, 160, 1);

                int s13 = _stream->GetOffset();
                _stream->WriteBoolean(false);
                int e13 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s13 - e13, s13 - 4);

                ByteStreamHelper::WriteBlockTag(*_stream, 2, 160, 1);

                int s14 = _stream->GetOffset();
                _stream->WriteBoolean(false);
                int e14 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s14 - e14, s14 - 4);

                _stream->WriteTaggedVInt(0, 3);

                ByteStreamHelper::WriteBlockTag(*_stream, 4, 160, 9);

                int s15 = _stream->GetOffset();
                _stream->WriteBoolean(true);
                {
                    _stream->WriteInt(0); // leaderboard timestamp end??
                    _stream->WriteInt(1787209200); // leaderboard timestamp start
                }
                int e15 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s15 - e15, s15 - 4);

                ByteStreamHelper::WriteBlockTag(*_stream, 5, 160, 1);

                int s16 = _stream->GetOffset();
                _stream->WriteBoolean(false);
                int e16 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s16 - e16, s16 - 4);

                _stream->WriteVInt(-1);
            }
            int e12 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s12 - e12, s12 - 4);

            // last stub (characters array)
            ByteStreamHelper::WriteBlockTag(*_stream, 27, 192, 1027);
            
            int s17 = _stream->GetOffset();
            _stream->WriteVInt(6); // characters array
            {   
                // barbarian
                _stream->WriteBoolean(true);
                {   
                    _stream->WriteTaggedVInt(107000012, 1);
                    _stream->WriteTaggedVInt(6, 2); // hero rank
                    _stream->WriteTaggedVInt(4, 3); // hero badges
                    _stream->WriteTaggedVInt(0, 4);

                    ByteStreamHelper::WriteTaggedBoolean(*_stream, 5, false);
                    ByteStreamHelper::WriteTaggedBoolean(*_stream, 6, false);
                    ByteStreamHelper::WriteTaggedBoolean(*_stream, 7, false);

                    _stream->WriteTaggedVInt(107000012, 8);
                    _stream->WriteTaggedVInt(1, 9);

                    ByteStreamHelper::WriteBlockTag(*_stream, 10, 192, 118);

                    int s18 = _stream->GetOffset();
                    _stream->WriteVInt(0);
                    int e18 = _stream->GetOffset();
                    _stream->WriteIntBigEndianAt(s18 - e18, s18 - 4);
                }
                
                // skip all other characters
                _stream->WriteBoolean(false);
                _stream->WriteBoolean(false);
                _stream->WriteBoolean(false);
                _stream->WriteBoolean(false);
                _stream->WriteBoolean(false);

                ByteStreamHelper::WriteBlockTag(*_stream, 27, 192, 1027);
                
                int s20 = _stream->GetOffset();
                _stream->WriteVInt(6);
                {
                    _stream->WriteVInt(5);
                    _stream->WriteVInt(2);
                    _stream->WriteVInt(2);
                    _stream->WriteVInt(2);
                    _stream->WriteVInt(2);
                    _stream->WriteVInt(2);
                }
                int e20 = _stream->GetOffset();
                _stream->WriteIntBigEndianAt(s20 - e20, s20 - 4);

                _stream->WriteVInt(-1);
            }
            int e17 = _stream->GetOffset();
            _stream->WriteIntBigEndianAt(s17 - e17, s17 - 4);

            _stream->WriteVInt(-1);
        }
        int e0 = _stream->GetOffset();
        _stream->WriteIntBigEndianAt(s0 - e0, s0 - 4);

        _stream->WriteTaggedVInt(0, 2);

        _stream->WriteVInt(-1);
    }

    int GetMessageType() override {
        return 20275;
    }
};