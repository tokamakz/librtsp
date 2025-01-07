
基于boost.asio开发一个rtsp库

选择boost.asio的原因：方便开发者集成librtsp库时，可以与其他通信库共用一个io_context


rtsp协议的优势：



|    协议名称    | 网络传输协议 | 延时  |        编码类型        |         HTML5支持情况          |
| :------------: | :----------: | :---: | :--------------------: | :----------------------------: |
|      RTSP      | TCP/UDP/组播 | 0~3s  |       H264/H265        | 不支持，（RTSP over HTTP除外） |
|      RTMP      |     TCP      | 0~3s  | H264/H265(CodecID =12) |             不支持             |
|      HLS       |  HTTP短连接  | 1~10s |       H264/H265        |         video标签支持          |
|    HTTP-FLV    |  HTTP长连接  | 0~3s  | H264/H265(CodecID =12) |     flv → fmp4 → video标签     |
|      webrtc    |  HTTP长连接  | 0~3s  |       H264/H265        |       video标签原生支持        |
|       srt  |  WebSocket   | 0~3s  | H264/H265(CodecID =12) |     flv → fmp4 → video标签     |


使用协程
线程池对外开放

支持H.264/H.265
支持rtsp client/server

支持UDP/TCP/组播三种方式推拉流


rtsp server
有人拉流时，触发通知
提供inputFrame接口，输入标准的H.264/H.265数据 


rtsp client
解析出标准的H.264/H.265 视频帧


example
ffmpeg rtsp推流验证rtsp server
结合sdl 做一个rtsp player


GOP
可配置
缓存一个GOP，实现秒开
或者不缓存


参考资料：
RTSP RFC: 2326
https://www.rfc-editor.org/rfc/rfc2326.html