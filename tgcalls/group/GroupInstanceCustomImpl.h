#ifndef TGCALLS_GROUP_INSTANCE_CUSTOM_IMPL_H
#define TGCALLS_GROUP_INSTANCE_CUSTOM_IMPL_H

#include <functional>
#include <vector>
#include <string>
#include <memory>
#include <map>

#include "../Instance.h"
#include "GroupInstanceImpl.h"

namespace tgcalls {

class LogSinkImpl;
class GroupInstanceCustomInternal;
class Threads;

class GroupInstanceCustomImpl final : public GroupInstanceInterface {
public:
    explicit GroupInstanceCustomImpl(GroupInstanceDescriptor &&descriptor);
    ~GroupInstanceCustomImpl();

    void stop();
    
    void setConnectionMode(GroupConnectionMode connectionMode, bool keepBroadcastIfWasEnabled);

    void emitJoinPayload(std::function<void(GroupJoinPayload const &)> completion);
    void setJoinResponsePayload(std::string const &payload);
    void addParticipants(std::vector<GroupParticipantDescription> &&participants);
    void removeSsrcs(std::vector<uint32_t> ssrcs);
    void removeIncomingVideoSource(uint32_t ssrc);

    void setIsMuted(bool isMuted);
    void setIsNoiseSuppressionEnabled(bool isNoiseSuppressionEnabled);
    void setVideoCapture(std::shared_ptr<VideoCaptureInterface> videoCapture);
    //void setVideoSource(std::function<webrtc::VideoTrackSourceInterface*()> getVideoSource);
    void setAudioOutputDevice(std::string id);
    void setAudioInputDevice(std::string id);
    
    void addIncomingVideoOutput(std::string const &endpointId, std::weak_ptr<rtc::VideoSinkInterface<webrtc::VideoFrame>> sink);
    
    void setVolume(uint32_t ssrc, double volume);
    void setFullSizeVideoEndpointId(std::string const &endpointId);

private:
    std::shared_ptr<Threads> _threads;
    std::unique_ptr<ThreadLocalObject<GroupInstanceCustomInternal>> _internal;
    std::unique_ptr<LogSinkImpl> _logSink;

};

} // namespace tgcalls

#endif
