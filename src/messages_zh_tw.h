#define MSG_TIMEOUT "逾时"
#define MSG_CAPABILITIES "无法切换性能"
#define MSG_CLIENT_CLOSED_CNX "用户端关闭联机"
#define MSG_CLIENT_READ_ERR "从用户端读取发生错误"
#define MSG_CANT_OPEN_CNX "无法开启联机"
#define MSG_CANT_CREATE_DATA_SOCKET "无法建立资料接口"
#define MSG_DEBUG_CLIENT_IS "用户端位址是"
#define MSG_SYNTAX_ERROR_IP "语法错误于IP位址"
#define MSG_PORT_SUCCESSFUL "PORT命令成功"
#define MSG_ONLY_IPV4V6 "仅支援IPv4与IPv6 (1,2)"
#define MSG_ONLY_IPV4 "仅支援IPv4 (1)"
#define MSG_TIMEOUT_PARSER "逾时 - 下回试试敲键时速度快一点"
#define MSG_LINE_TOO_LONG "命令行过长"
#define MSG_LOG_OVERFLOW "用户尝试要溢满命令行缓冲区"
#define MSG_GOODBYE "再见。您上传%llu并下载%llu kbytes."
#define MSG_DEBUG_COMMAND "命令"
#define MSG_IS_YOUR_CURRENT_LOCATION "是您目前的位置"
#define MSG_NOT_LOGGED_IN "您并未登入"
#define MSG_AUTH_UNIMPLEMENTED "安全扩充项未实施"
#define MSG_NO_FILE_NAME "无档案名称"
#define MSG_NO_DIRECTORY_NAME "无目录名称"
#define MSG_NO_RESTART_POINT "无重新开始点"
#define MSG_ABOR_SUCCESS "ABOR成功"
#define MSG_MISSING_ARG "遗失参数"
#define MSG_GARBAGE_FOUND "参数值后有无用的字串"
#define MSG_VALUE_TOO_LARGE "参数值过大"
#define MSG_IDLE_TIME "闲置时间设为 %lu 秒"
#define MSG_SITE_HELP "下列的SITE命令被认可"
#define MSG_BAD_CHMOD "无效的权限"
#define MSG_UNKNOWN_EXTENSION "是不明的扩充项"
#define MSG_XDBG_OK "XDBG命令成功，除错程度现在是 %d"
#define MSG_UNKNOWN_COMMAND "不明的命令"
#define MSG_TIMEOUT_NOOP "逾时 (已 %lu 秒无操作)"
#define MSG_TIMEOUT_DATA "逾时 (已 %lu 秒无新资料)"
#define MSG_SLEEPING "Zzz..."
#define MSG_ALREADY_LOGGED "您已经登入"
#define MSG_ANY_PASSWORD "任何密码都可用"
#define MSG_ANONYMOUS_LOGGED "匿名使用者登入"
#define MSG_ANONYMOUS_LOGGED_VIRTUAL "匿名使用者登入到虚拟FTP"
#define MSG_USER_OK "使用者 %s OK. 需要密码."
#define MSG_CANT_DO_TWICE "在目前联机期间无法做到"
#define MSG_UNABLE_SECURE_ANON "无法设定安全的匿名FTP"
#define MSG_BANDWIDTH_RESTRICTED "您的频宽使用受限制"
#define MSG_NO_PASSWORD_NEEDED "任何密码都可用"
#define MSG_NOTRUST "抱歉，我无法信任您"
#define MSG_WHOAREYOU "请告诉我你是谁"
#define MSG_AUTH_FAILED "验证失败，抱歉"
#define MSG_AUTH_TOOMANY "验证失败太多次"
#define MSG_NO_HOMEDIR "没有家目录 - 取消"
#define MSG_NO_HOMEDIR2 "%s 不存在或无法到达"
#define MSG_START_SLASH "开始于 /"
#define MSG_USER_GROUP_ACCESS "使用者 %s 有群组存取于"
#define MSG_FXP_SUPPORT "这个服务器支援FXP传输"
#define MSG_RATIO "您必须遵守 %u:%u (UL/DL) 比率"
#define MSG_CHROOT_FAILED "无法设定安全的chroot() jail"
#define MSG_CURRENT_DIR_IS "OK. 目前的目录是 %s"
#define MSG_CURRENT_RESTRICTED_DIR_IS "OK. 目前限制的目录是 %s"
#define MSG_IS_NOW_LOGGED_IN "%s 现在登入"
#define MSG_CANT_CHANGE_DIR "无法变更目录到 %s"
#define MSG_PATH_TOO_LONG "路径太长"
#define MSG_CANT_PASV "您不能在IPv6联机使用PASV。请改用EPSV。"
#define MSG_CANT_PASSIVE "无法开启被动联机"
#define MSG_PORTS_BUSY "所有保留的TCP ports都正忙碌中"
#define MSG_GETSOCKNAME_DATA "无法辨识本机资料接口"
#define MSG_GETPEERNAME "无法辨识本机接口"
#define MSG_INVALID_IP "抱歉，给的是无效的位址"
#define MSG_NO_EPSV "请使用的符合IPv6并支援EPSV的用户端"
#define MSG_BAD_PORT "抱歉，无法联机到 ports < 1024"
#define MSG_NO_FXP "我不能开启联机到 %s (仅 %s)"
#define MSG_FXP "FXP传输: 从 %s 到 %s"
#define MSG_NO_DATA_CONN "无资料联机"
#define MSG_ACCEPT_FAILED "联机无法被接受"
#define MSG_ACCEPT_SUCCESS "接受资料联机"
#define MSG_CNX_PORT_FAILED "无法开启资料联机到port %d"
#define MSG_CNX_PORT "联机到port %d"
#define MSG_ANON_CANT_MKD "抱歉，不允许匿名使用者建立目录"
#define MSG_ANON_CANT_RMD "抱歉，不允许匿名使用者移除目录"
#define MSG_ANON_CANT_RENAME "不允许匿名使用者搬移/更名档案"
#define MSG_ANON_CANT_CHANGE_PERMS "匿名使用者不能变更权限"
#define MSG_GLOB_NO_MEMORY "形成 %s 时，内存不足"
#define MSG_PROBABLY_DENIED "(这可能意味 \"权限被拒\")"
#define MSG_GLOB_READ_ERROR "形成 %s 时发生读取错误"
#define MSG_GLOB_NO_MATCH "没有符合的 %s ，于 %s 中"
#define MSG_CHMOD_FAILED "不能变更 %s 权限"
#define MSG_CHMOD_SUCCESS " %s 权限已变更"
#define MSG_CHMOD_TOTAL_FAILURE "抱歉，我无法变更任何权限"
#define MSG_ANON_CANT_DELETE "匿名使用者不能删除档案"
#define MSG_ANON_CANT_OVERWRITE "匿名使用者不能覆写现存的档案"
#define MSG_DELE_FAILED "无法删除 %s"
#define MSG_DELE_SUCCESS "删除 %s"
#define MSG_DELE_TOTAL_FAILURE "没有删除档案"
#define MSG_LOAD_TOO_HIGH \
    "当您联机时负载是 %3.2f 。负载如此高时，我们不允许匿名使用者下载。 \n" \
    "上传则都是允许的"

#define MSG_OPEN_FAILURE "无法开启 %s"
#define MSG_OPEN_FAILURE2 "无法开启那个档案"
#define MSG_STAT_FAILURE "无法找到档案大小"
#define MSG_STAT_FAILURE2 "无法检查档案存在性"
#define MSG_REST_TOO_LARGE_FOR_FILE "重新开始offset %lld 过大，针对档案大小 %lld时。"
#define MSG_REST_RESET "offset重设为 0 重新开始"
#define MSG_NOT_REGULAR_FILE "我只能抓取一般档案"
#define MSG_NOT_MODERATED \
    "此档由匿名使用者上传。\n" \
    "还没有被站台管理员核准供下载。"
#define MSG_RATIO_DENIAL \
    "抱歉，上传/下载率是 %u:%u 。\n" \
    "您目前上传 %llu Kb 下载 %llu Kb。\n" \
    "请上传一些好东西然后晚点再尝试抓取。"
#define MSG_NO_MORE_TO_DOWNLOAD "已没东西可下载"
#define MSG_WINNER "电脑是您的朋友。信任电脑"
#define MSG_KBYTES_LEFT "剩 %.1f 供下载"
#define MSG_ABORTED "传输中止"
#define MSG_DATA_WRITE_FAILED "资料联机写入时发生错误"
#define MSG_DATA_READ_FAILED "资料联机读取时发生错误"
#define MSG_MMAP_FAILED "无法将档案map进内存"
#define MSG_WRITE_FAILED "写入档案时发生错误"
#define MSG_TRANSFER_RATE_M "%.3f 秒 (到目前), %.2f Mbytes 每秒"
#define MSG_TRANSFER_RATE_K "%.3f 秒 (到目前), %.2f Kbytes 每秒"
#define MSG_TRANSFER_RATE_B "%.3f 秒 (到目前), %.2f bytes 每秒"
#define MSG_SPACE_FREE_M "%.1f Mbytes 剩余硬碟空间"
#define MSG_SPACE_FREE_K "%f Kbytes 剩余硬碟空间"
#define MSG_DOWNLOADED "已下载"
#define MSG_REST_NOT_NUMERIC "REST需要数字参数"
#define MSG_REST_ASCII_STRICT "在ASCII模式回应标记必须是 0"
#define MSG_REST_ASCII_WORKAROUND "重新开始于 %lld。但是我们在ASCII模式"
#define MSG_REST_SUCCESS "重新开始于 %lld"
#define MSG_SANITY_DIRECTORY_FAILURE "禁止的目录名称"
#define MSG_SANITY_FILE_FAILURE "禁止的档名: %s"
#define MSG_MKD_FAILURE "无法建立目录"
#define MSG_MKD_SUCCESS "建立目录成功"
#define MSG_RMD_FAILURE "无法移除目录"
#define MSG_RMD_SUCCESS "移除目录成功"
#define MSG_TIMESTAMP_FAILURE "无法取得时间戳记"
#define MSG_MODE_ERROR "只支援ASCII及binary模式"
#define MSG_CREATE_FAILURE "无法建立标案"
#define MSG_ABRT_ONLY "当上传时ABRT唯一合法的命令"
#define MSG_UPLOAD_PARTIAL "部份上传"
#define MSG_REMOVED "移除了"
#define MSG_UPLOADED "上传了"
#define MSG_GMTIME_FAILURE "无法取得当地时间"
#define MSG_TYPE_8BIT_FAILURE "只支援8-bit bytes，我们不是在十年前的年代"
#define MSG_TYPE_UNKNOWN "不明的TYPE"
#define MSG_TYPE_SUCCESS "TYPE目前是"
#define MSG_STRU_FAILURE "只支援F(ile)"
#define MSG_MODE_FAILURE "请使用S(tream)模式"
#define MSG_RENAME_ABORT "中止之前的更名操作"
#define MSG_RENAME_RNFR_SUCCESS "RNFR接受 - 档案存在，准备到目的"
#define MSG_FILE_DOESNT_EXIST "抱歉，档案不存在"
#define MSG_RENAME_ALREADY_THERE "RENAME失败 - 目的档案已经存在"
#define MSG_RENAME_NORNFR "RNTO前需要RNFR"
#define MSG_RENAME_FAILURE "更名/移动失败"
#define MSG_RENAME_SUCCESS "档案更名/移动成功"
#define MSG_NO_SUPERSERVER "请在super-server (like tcpserver)中执行pure-ftpd"
#define MSG_NO_FTP_ACCOUNT "无法找到'ftp'帐号"
#define MSG_CONF_ERR "组态设定错误"
#define MSG_NO_VIRTUAL_FILE "遗失虚拟使用者档名"
#define MSG_ILLEGAL_THROTTLING "不合法的节流值"
#define MSG_ILLEGAL_TRUSTED_GID "不合法的chroot信任gid"
#define MSG_ILLEGAL_USER_LIMIT "不合法的使用者限制"
#define MSG_ILLEGAL_FACILITY "不明的记录设施名称"
#define MSG_ILLEGAL_CONFIG_FILE_LDAP "无效的LDAP组态档案"
#define MSG_ILLEGAL_LOAD_LIMIT "不合法的负载限制"
#define MSG_ILLEGAL_PORTS_RANGE "不合法的埠口范围"
#define MSG_ILLEGAL_LS_LIMITS "不合法的'ls'限制"
#define MSG_ILLEGAL_FORCE_PASSIVE "不合法的被动联机强制IP"
#define MSG_ILLEGAL_RATIO "不合法的上传/下载率"
#define MSG_ILLEGAL_UID_LIMIT "不合法的uid限制"
#define MSG_ILLEGAL_OPTION "不明的run-time选项"
#define MSG_LDAP_MISSING_BASE "LDAP组态档中遗失LDAPBaseDN"
#define MSG_LDAP_WRONG_PARMS "错误的LDAP参数"
#define MSG_NEW_CONNECTION "自 %s 的新联机"
#define MSG_WELCOME_TO "欢迎来到"
#define MSG_MAX_USERS "%lu 使用者(最大值)已经登入，抱歉"
#define MSG_NB_USERS "您是第 %d 个使用者， %d 允许"
#define MSG_WELCOME_TIME "本地时间现在是 %02d:%02d 负载是 %3.2f。服务器埠口: %u。"
#define MSG_ANONYMOUS_FTP_ONLY "这里只允许匿名FTP"
#define MSG_RATIOS_EVERYONE "针对EVERYONE启用比率:"
#define MSG_RATIOS_ANONYMOUS "匿名使用者规定用UL/DL率:"
#define MSG_RATIOS_RULE "要下载 %u Mb, 先义务上传 %u Mb 的好东西。"
#define MSG_INFO_IDLE_M "在 %lu 分钟内没有活动，您被会断线。"
#define MSG_INFO_IDLE_S "在 %lu 秒内没有活动，您被会断线。"
#define MSG_INFO_CPU_TIME "注销 - CPU 时间花费: %ld.%03ld 秒。"
#define MSG_CANT_READ_FILE "抱歉，我们无法读取[%s]"
#define MSG_LS_TRUNCATED "输出截短到 %u 符合"
#define MSG_LS_SUCCESS "总共 %u 符合"
#define MSG_LOGOUT "注销"
#define MSG_AUTH_FAILED_LOG "使用者[%s]验证失败"
#define MSG_ILLEGAL_UMASK "无效的umask"
#define MSG_STANDALONE_FAILED "无法启动standalone server"
#define MSG_NO_ANONYMOUS_LOGIN "这是私用系统 - 不开放匿名登入"
#define MSG_ANONYMOUS_ANY_PASSWORD "任何密码都可用"
#define MSG_MAX_USERS_IP "太多联机 (%lu) 从此 IP"
#define MSG_ACTIVE_DISABLED "主动模式关闭"
#define MSG_TRANSFER_SUCCESSFUL "档案传送成功"
#define MSG_NO_DISK_SPACE "硬碟爆满 - 请晚点上传"
#define MSG_OUT_OF_MEMORY "内存不足"
#define MSG_ILLEGAL_TRUSTED_IP "不合法的信任IP位址"
#define MSG_NO_ASCII_RESUME "ASCII重传并不安全，请先删除档案"
#define MSG_UNKNOWN_ALTLOG "不明的记录档格式"
#define MSG_ACCOUNT_DISABLED "无法登入成[%s]: 帐号关闭"
#define MSG_SQL_WRONG_PARMS "错误的SQL参数"
#define MSG_ILLEGAL_CONFIG_FILE_SQL "无效的SQL设定档"
#define MSG_SQL_MISSING_SERVER "SQL组态档中遗失服务器设定"
#define MSG_SQL_DOWN "SQL server好像关机了"
#define MSG_ILLEGAL_QUOTA "无效的额度"
#define MSG_QUOTA_FILES "%llu 档案数使用 (%d%%) - 授权可用: %llu 个档案"
#define MSG_QUOTA_SIZE "%llu Kbytes使用 (%d%%) - 授权可用: %llu Kb"
#define MSG_QUOTA_EXCEEDED "超过额度: %s 不会被储存"
#define MSG_AUTH_UNKNOWN "不明的验证方法"
#define MSG_PDB_BROKEN "无法读取indexed puredb档(或侦测到旧格式) - 试试 pure-pw mkdb"
#define MSG_ALIASES_ALIAS "%s 是别名，给 %s 的"
#define MSG_ALIASES_UNKNOWN "不明的别名 %s。"
#define MSG_ALIASES_BROKEN_FILE "损坏的别名档案"
#define MSG_ALIASES_LIST "以下的别名可用:"
#define MSG_PERUSER_MAX "礚猭钡ㄓㄏノ禬筁 %lu 硈絬计"
#define MSG_IPV6_OK "硂场诀舧IPv6硈絬"
