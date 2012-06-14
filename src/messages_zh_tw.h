#define MSG_TIMEOUT "逾時"
#define MSG_CAPABILITIES "無法切換性能"
#define MSG_CLIENT_CLOSED_CNX "用戶端關閉連線"
#define MSG_CLIENT_READ_ERR "從用戶端讀取發生錯誤"
#define MSG_CANT_OPEN_CNX "無法開啟連線"
#define MSG_CANT_CREATE_DATA_SOCKET "無法建立資料接口"
#define MSG_DEBUG_CLIENT_IS "用戶端位址是"
#define MSG_SYNTAX_ERROR_IP "語法錯誤於IP位址"
#define MSG_PORT_SUCCESSFUL "PORT命令OK"
#define MSG_ONLY_IPV4V6 "僅支援IPv4與IPv6 (1,2)"
#define MSG_ONLY_IPV4 "僅支援IPv4 (1)"
#define MSG_TIMEOUT_PARSER "逾時 - 下回試試敲鍵時速度快一點"
#define MSG_LINE_TOO_LONG "命令行過長"
#define MSG_LOG_OVERFLOW "用戶嘗試要溢滿命令行緩衝區"
#define MSG_GOODBYE "再見。您上傳%llu並下載%llu kbytes."
#define MSG_DEBUG_COMMAND "命令"
#define MSG_IS_YOUR_CURRENT_LOCATION "是您目前的位置"
#define MSG_NOT_LOGGED_IN "您並未登入"
#define MSG_AUTH_UNIMPLEMENTED "安全擴充項未實施"
#define MSG_NO_FILE_NAME "無檔案名稱"
#define MSG_NO_DIRECTORY_NAME "無目錄名稱"
#define MSG_NO_RESTART_POINT "無重新開始點"
#define MSG_ABOR_SUCCESS "ABOR OK"
#define MSG_MISSING_ARG "遺失參數"
#define MSG_GARBAGE_FOUND "參數值後有無用的字串"
#define MSG_VALUE_TOO_LARGE "參數值過大"
#define MSG_IDLE_TIME "閒置時間設為 %lu 秒"
#define MSG_SITE_HELP "下列的SITE命令被認可"
#define MSG_BAD_CHMOD "無效的權限"
#define MSG_UNKNOWN_EXTENSION "是不明的擴充項"
#define MSG_XDBG_OK "XDBG命令OK，除錯程度現在是 %d"
#define MSG_UNKNOWN_COMMAND "不明的命令"
#define MSG_TIMEOUT_NOOP "逾時 (已 %lu 秒無操作)"
#define MSG_TIMEOUT_DATA "逾時 (已 %lu 秒無新資料)"
#define MSG_SLEEPING "Zzz..."
#define MSG_ALREADY_LOGGED "您已經登入"
#define MSG_ANY_PASSWORD "任何密碼都可用"
#define MSG_ANONYMOUS_LOGGED "匿名使用者登入"
#define MSG_ANONYMOUS_LOGGED_VIRTUAL "匿名使用者登入到虛擬FTP"
#define MSG_USER_OK "使用者 %s OK. 需要密碼."
#define MSG_CANT_DO_TWICE "在目前連線期間不能這樣做"
#define MSG_UNABLE_SECURE_ANON "無法建立安全匿名FTP"
#define MSG_BANDWIDTH_RESTRICTED "您的頻寬使用受限制"
#define MSG_NO_PASSWORD_NEEDED "任何密碼都可用"
#define MSG_NOTRUST "抱歉，我無法信任您"
#define MSG_WHOAREYOU "請告訴我你是誰"
#define MSG_AUTH_FAILED "驗證失敗，抱歉"
#define MSG_AUTH_TOOMANY "驗證失敗太多次"
#define MSG_NO_HOMEDIR "沒有家目錄 - 取消"
#define MSG_NO_HOMEDIR2 "%s 不存在或無法到達"
#define MSG_START_SLASH "開始於 /"
#define MSG_USER_GROUP_ACCESS "使用者 %s 有群組存取於"
#define MSG_FXP_SUPPORT "這個伺服器支援FXP傳輸"
#define MSG_RATIO "您必須遵守 %u:%u (UL/DL) 比率"
#define MSG_CHROOT_FAILED "無法設定安全的chroot() jail"
#define MSG_CURRENT_DIR_IS "OK. 目前的目錄是 %s"
#define MSG_CURRENT_RESTRICTED_DIR_IS "OK. 目前限制的目錄是 %s"
#define MSG_IS_NOW_LOGGED_IN "%s 現在登入"
#define MSG_CANT_CHANGE_DIR "無法變更目錄到 %s"
#define MSG_PATH_TOO_LONG "路徑太長"
#define MSG_CANT_PASV "您不能在IPv6連線使用PASV。請改用EPSV。"
#define MSG_CANT_PASSIVE "無法開啟被動式連線"
#define MSG_PORTS_BUSY "所有保留的TCP ports都正忙碌中"
#define MSG_GETSOCKNAME_DATA "無法辨識本機資料接口"
#define MSG_GETPEERNAME "無法辨識本機接口"
#define MSG_INVALID_IP "抱歉，給的是無效的位址"
#define MSG_NO_EPSV "請使用符合IPv6並支援EPSV的用戶端"
#define MSG_BAD_PORT "抱歉，無法連線到 ports < 1024"
#define MSG_NO_FXP "我不能開啟連線到 %s (僅 %s)"
#define MSG_FXP "FXP傳輸: 從 %s 到 %s"
#define MSG_NO_DATA_CONN "無資料連線"
#define MSG_ACCEPT_FAILED "連線無法被接受"
#define MSG_ACCEPT_SUCCESS "接受資料連線"
#define MSG_CNX_PORT_FAILED "無法開啟資料連線到port %d"
#define MSG_CNX_PORT "連線到port %d"
#define MSG_ANON_CANT_MKD "抱歉，不准匿名使用者建立目錄"
#define MSG_ANON_CANT_RMD "抱歉，不准匿名使用者移除目錄"
#define MSG_ANON_CANT_RENAME "不准匿名使用者搬移/更名檔案"
#define MSG_ANON_CANT_CHANGE_PERMS "匿名使用者不能變更權限"
#define MSG_GLOB_NO_MEMORY "形成 %s 時，記憶體不足"
#define MSG_PROBABLY_DENIED "(這可能意味 \"權限被拒\")"
#define MSG_GLOB_READ_ERROR "形成 %s 時發生讀取錯誤"
#define MSG_GLOB_NO_MATCH "沒有符合的 %s ，於 %s 中"
#define MSG_CHMOD_FAILED "不能變更 %s 權限"
#define MSG_CHMOD_SUCCESS " %s 權限已變更"
#define MSG_CHMOD_TOTAL_FAILURE "抱歉，我無法變更任何權限"
#define MSG_ANON_CANT_DELETE "匿名使用者不能刪除檔案"
#define MSG_ANON_CANT_OVERWRITE "匿名使用者不能覆寫現存的檔案"
#define MSG_DELE_FAILED "無法刪除 %s"
#define MSG_DELE_SUCCESS "刪除 %s"
#define MSG_DELE_TOTAL_FAILURE "沒有刪除檔案"
#define MSG_LOAD_TOO_HIGH "當您連線時負載是 %3.2f 。負載如此高時，我們不准匿名使用者下載。\n上傳則都是可以的"



#define MSG_OPEN_FAILURE "無法開啟 %s"
#define MSG_OPEN_FAILURE2 "無法開啟那個檔案"
#define MSG_STAT_FAILURE "無法找到檔案大小"
#define MSG_STAT_FAILURE2 "無法檢查檔案的存在性"
#define MSG_REST_TOO_LARGE_FOR_FILE "針對檔案大小 %lld時，重新開始offset %lld 會過大。"
#define MSG_REST_RESET "offset重設為 0 重新開始"
#define MSG_NOT_REGULAR_FILE "我只能抓取一般檔案"
#define MSG_NOT_MODERATED "此檔由匿名使用者上傳。\n還沒有被站台管理員核准供下載。"


#define MSG_RATIO_DENIAL "抱歉，上傳/下載率是 %u:%u 。\n您目前上傳 %llu Kb 下載 %llu Kb。\n請上傳一些好東西然後晚點再嘗試抓取。"



#define MSG_NO_MORE_TO_DOWNLOAD "已沒東西可下載"
#define MSG_WINNER "電腦是您的朋友。信任電腦"
#define MSG_KBYTES_LEFT "剩 %.1f kbytes要下載"
#define MSG_ABORTED "傳輸中止"
#define MSG_DATA_WRITE_FAILED "資料連線寫入時發生錯誤"
#define MSG_DATA_READ_FAILED "資料連線讀取時發生錯誤"
#define MSG_MMAP_FAILED "無法將檔案map進記憶體"
#define MSG_WRITE_FAILED "寫入檔案時發生錯誤"
#define MSG_TRANSFER_RATE_M "%.3f 秒 (到目前),每秒 %.2f Mbytes"
#define MSG_TRANSFER_RATE_K "%.3f 秒 (到目前),每秒 %.2f Kbytes"
#define MSG_TRANSFER_RATE_B "%.3f 秒 (到目前),每秒 %.2f bytes"
#define MSG_SPACE_FREE_M "%.1f Mbytes 剩餘硬碟空間"
#define MSG_SPACE_FREE_K "%f Kbytes 剩餘硬碟空間"
#define MSG_DOWNLOADED "已下載"
#define MSG_REST_NOT_NUMERIC "REST需要數字參數"
#define MSG_REST_ASCII_STRICT "在ASCII模式回應標記必須是 0"
#define MSG_REST_ASCII_WORKAROUND "重新開始於 %lld。但是我們在ASCII模式"
#define MSG_REST_SUCCESS "重新開始於 %lld"
#define MSG_SANITY_DIRECTORY_FAILURE "禁用的目錄名稱"
#define MSG_SANITY_FILE_FAILURE "禁用的檔名: %s"
#define MSG_MKD_FAILURE "無法建立目錄"
#define MSG_MKD_SUCCESS "建立目錄OK"
#define MSG_RMD_FAILURE "無法移除目錄"
#define MSG_RMD_SUCCESS "移除目錄OK"
#define MSG_TIMESTAMP_FAILURE "無法取得時間戳記"
#define MSG_MODE_ERROR "只支援ASCII及binary模式"
#define MSG_CREATE_FAILURE "無法建立檔案"
#define MSG_ABRT_ONLY "當上傳時ABRT是唯一能用的命令"
#define MSG_UPLOAD_PARTIAL "部份上傳"
#define MSG_REMOVED "移除了"
#define MSG_UPLOADED "上傳了"
#define MSG_GMTIME_FAILURE "無法取得當地時間"
#define MSG_TYPE_8BIT_FAILURE "只支援8-bit bytes，我們不是在十年前的年代"
#define MSG_TYPE_UNKNOWN "不明的TYPE"
#define MSG_TYPE_SUCCESS "TYPE目前是"
#define MSG_STRU_FAILURE "只支援F(ile)"
#define MSG_MODE_FAILURE "請使用S(tream)模式"
#define MSG_RENAME_ABORT "中止之前的更名操作"
#define MSG_RENAME_RNFR_SUCCESS "RNFR接受 - 檔案存在，準備到目的地"
#define MSG_FILE_DOESNT_EXIST "抱歉，檔案不存在"
#define MSG_RENAME_ALREADY_THERE "RENAME失敗 - 目的檔案已經存在"
#define MSG_RENAME_NORNFR "RNTO前需要RNFR"
#define MSG_RENAME_FAILURE "更名/移動失敗"
#define MSG_RENAME_SUCCESS "檔案更名/移動OK"
#define MSG_NO_SUPERSERVER "請在super-server (like tcpserver)中執行pure-ftpd"
#define MSG_NO_FTP_ACCOUNT "無法找到'ftp'帳號"
#define MSG_CONF_ERR "組態設定錯誤"
#define MSG_NO_VIRTUAL_FILE "遺失虛擬使用者檔名"
#define MSG_ILLEGAL_THROTTLING "不合法的節流值"
#define MSG_ILLEGAL_TRUSTED_GID "不合法的chroot信任gid"
#define MSG_ILLEGAL_USER_LIMIT "不合法的使用者限制"
#define MSG_ILLEGAL_FACILITY "不明的記錄設施名稱"
#define MSG_ILLEGAL_CONFIG_FILE_LDAP "無效的LDAP組態檔案"
#define MSG_ILLEGAL_LOAD_LIMIT "不合法的負載限制"
#define MSG_ILLEGAL_PORTS_RANGE "不合法的埠口範圍"
#define MSG_ILLEGAL_LS_LIMITS "不合法的'ls'限制"
#define MSG_ILLEGAL_FORCE_PASSIVE "被動式連線時，不合法的強制IP"
#define MSG_ILLEGAL_RATIO "不合法的上傳/下載率"
#define MSG_ILLEGAL_UID_LIMIT "不合法的uid限制"
#define MSG_ILLEGAL_OPTION "不明的run-time選項"
#define MSG_LDAP_MISSING_BASE "LDAP組態檔中遺失LDAPBaseDN"
#define MSG_LDAP_WRONG_PARMS "錯誤的LDAP參數"
#define MSG_NEW_CONNECTION "自 %s 的新連線"
#define MSG_WELCOME_TO "歡迎來到"
#define MSG_MAX_USERS "%lu 使用者(最大值)已經登入，抱歉"
#define MSG_NB_USERS "您是第 %d 個使用者，最多可達 %d 個連線"
#define MSG_WELCOME_TIME "現在本地時間是 %02d:%02d 。伺服器埠口: %u。"
#define MSG_ANONYMOUS_FTP_ONLY "這裡只用匿名FTP"
#define MSG_RATIOS_EVERYONE "針對EVERYONE啟用比率:"
#define MSG_RATIOS_ANONYMOUS "匿名使用者規定用UL/DL率:"
#define MSG_RATIOS_RULE "要下載 %u Mb, 先義務上傳 %u Mb 的好東西。"
#define MSG_INFO_IDLE_M "在 %lu 分鐘內沒有活動，您被會斷線。"
#define MSG_INFO_IDLE_S "在 %lu 秒內沒有活動，您被會斷線。"
#define MSG_CANT_READ_FILE "抱歉，我們無法讀取[%s]"
#define MSG_LS_TRUNCATED "輸出截短到 %u 符合"
#define MSG_LS_SUCCESS "總共 %u 符合"
#define MSG_LOGOUT "登出."
#define MSG_AUTH_FAILED_LOG "使用者[%s]驗證失敗"
#define MSG_ILLEGAL_UMASK "無效的umask"
#define MSG_STANDALONE_FAILED "無法啟動standalone server"
#define MSG_NO_ANONYMOUS_LOGIN "這是私用系統 - 不開放匿名登入"
#define MSG_ANONYMOUS_ANY_PASSWORD "任何密碼都可用"
#define MSG_MAX_USERS_IP "太多連線 (%lu) 來自這個 IP"
#define MSG_ACTIVE_DISABLED "主動模式關閉"
#define MSG_TRANSFER_SUCCESSFUL "檔案傳送OK"
#define MSG_NO_DISK_SPACE "硬碟爆滿 - 請晚點上傳"
#define MSG_OUT_OF_MEMORY "記憶體不足"
#define MSG_ILLEGAL_TRUSTED_IP "不合法的信任IP位址"
#define MSG_NO_ASCII_RESUME "ASCII重傳並不安全，請先刪除檔案"
#define MSG_UNKNOWN_ALTLOG "不明的記錄檔格式"
#define MSG_ACCOUNT_DISABLED "無法登入為[%s]: 帳號關閉"
#define MSG_SQL_WRONG_PARMS "錯誤的SQL參數"
#define MSG_ILLEGAL_CONFIG_FILE_SQL "無效的SQL設定檔"
#define MSG_SQL_MISSING_SERVER "SQL組態檔中遺失伺服器設定"
#define MSG_SQL_DOWN "SQL server好像關機了"
#define MSG_ILLEGAL_QUOTA "無效的額度"
#define MSG_QUOTA_FILES "%llu 檔案數使用 (%d%%) - 授權可用: %llu 個檔案"
#define MSG_QUOTA_SIZE "%llu Kbytes使用 (%d%%) - 授權可用: %llu Kb"
#define MSG_QUOTA_EXCEEDED "超過額度: [%s] 不會被儲存"
#define MSG_AUTH_UNKNOWN "不明的驗證方法"
#define MSG_PDB_BROKEN "無法讀取indexed puredb檔(或偵測到舊格式) - 試試 pure-pw mkdb"
#define MSG_ALIASES_ALIAS "%s 是別名，給 %s 的"
#define MSG_ALIASES_UNKNOWN "不明的別名 %s。"
#define MSG_ALIASES_BROKEN_FILE "損壞的別名檔案"
#define MSG_ALIASES_LIST "以下的別名可用："
#define MSG_PERUSER_MAX "無法接受來自同一使用者超過 %lu 的連線數"
#define MSG_IPV6_OK "這部主機也歡迎IPv6的連線"
#define MSG_TLS_INFO "SSL/TLS: 啟用 %s with %s, %d 位元加密"
#define MSG_TLS_WEAK "SSL/TLS: 密碼不足"
#define MSG_TLS_NEEDED "抱歉，此伺服器不接受明文式連線。\n" \
    "請使用SSL/TLS的安全機制重新連線。"
#define MSG_ILLEGAL_CHARSET "Illegal charset"
#define MSG_TLS_NO_CTX "SSL/TLS: Context not found. Exiting."
#define MSG_PROT_OK "Data protection level set to \"%s\""
#define MSG_PROT_PRIVATE_NEEDED "Data connection cannot be opened with this PROT setting."
#define MSG_PROT_UNKNOWN_LEVEL "Protection level %s not understood. Fallback to \"%s\""
#define MSG_PROT_BEFORE_PBSZ "PROT must be preceded by a successful PBSZ command"
#define MSG_WARN_LDAP_USERPASS_EMPTY "LDAP returned no userPassword attribute, check LDAP access rights."
#define MSG_LDAP_INVALID_AUTH_METHOD "Invalid LDAPAuthMethod in the configuration file. Should be 'bind' or 'password'."
