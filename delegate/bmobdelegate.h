/**
* create by zhou,2016-03-15
* delegate of bmob sdk
*/
#ifndef BMOBSDK_BMOBDELEGATE_H_
#define BMOBSDK_BMOBDELEGATE_H_


namespace bmobdelegate{

    /**
    * sdk初始化回调接口
    */
    class BmobInitDelegate{
    public:
        /**
        * 初始化成功回调
        * @param data const void* 返回的数据
        * @return void
        */
        virtual void onInitSuccess(const void* data) = 0;
        /**
        * 初始化失败回调
        * @param code const int 失败的代码
        * @param data const void* 失败的返回数据
        * @return void
        */
        virtual void onInitFail(const int code,const void* data) = 0;
    };

    /**
    * 保存对象回调接口
    */
    class BmobSaveDelegate{
    public:
    	/**
    	* 保存数据成功的回调接口
    	* @param data 返回的数据
    	*/
    	virtual void onSaveSucess(const void* data) = 0;
    	/**
    	* 保存错误回调接口
    	* @param code 返回的错误码
    	* @param data 返回的错误信息
    	*/
    	virtual void onSaveError(int code,const void* data) = 0;
    };

    /**
    * 重置密码回调接口
    */
    class BmobResetPasswordDelegate{
    public:
    	/**
    	* 重置成功的回调接口
    	*/
    	virtual void onResetSucess(const void* data) = 0;
    	/**
    	* 重置失败回调接口
    	*/
    	virtual void onResetError(int code,const void* data) = 0;
    };

    /**
    * 请求验证码回调接口
    */
    class BmobRequestSMSCodeDelegate{
    public:
        /**
        * 请求SMS码的回调函数
        * @param code int 返回代码
        * @param data const void* data 返回的数据
        */
        virtual void onRequestDone(int code,const void* data) = 0;
    };

    /**
    * 通过验证码重置密码回调接口
    */
    class BmobResetPasswordByCodeDelegate{
    public:
        /**
    	* 通过验证码重置密码的回调函数
    	* @param code int 返回的代码
    	* @param data const void*	返回的数据
    	*/
    	virtual void onResetDone(int code,const void* data) = 0;
    };

    /**
    * 用户登陆回调接口
    */
    class BmobLoginDelegate{
    public:
    	/**
    	*
    	*/
    	virtual void onLoginDone(int code,const void* data) = 0;
    };

    /**
    * 获取服务器时间回调接口
    */
    class BmobGetTimeDelegate{
    public:
    	/**
    	* 获取服务时间回调
    * @param code 返回状态码
    	* @param data 返回的数据
    	*/
    	virtual void onGetTime(int code,const void* data) = 0;
    };

    /**
    * 查询单个数据回调接口
    */
    class BmobGetDelegate{
    public:
    	/**
    	* 查询成功的回调
    	* @param data 返回的数据
    	*/
    	virtual void onGetSucess(const void* data) = 0;
    	/**
    	* 失败回调
    	* @param code 返回错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onGetError(int code,const void* data) = 0;
    };

    /**
    * 查询所有回调接口
    */
    class BmobFindDelegate{
    public:
    	/**
    	* 成功回调接口
    	* @param data 返回的数据
    	*/
    	virtual void onFindSucess(const void* data) = 0;
    	/**
    	* 错误回调
    	* @param code 返回的错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onFindError(int code,const void* data) = 0;
    };


    /**
    * 邮箱验证回调接口
    */
    class BmobEmailVerifyDelegate{
    public:
    	/**
    	* 验证成功的回调接口
    	* @param data 返回的数据
    	*/
    	virtual void onEmailVerifySucess(const void* data) = 0;
    	/**
    	* 验证失败回调
    	* @param code 返回的错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onEmailVerifyError(int code,const void* data) = 0;
    };

    /**
    * 删除对象回调接口
    */
    class BmobDeleteDelegate{
    public:
    	/**
    	* 删除成功的回调方法
    	* @param data 返回的数据
    	*/
    	virtual void onDeleteSucess(const void* data) = 0;
    	/**
    	* 删除失败回调方法
    	* @param code 返回错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onDeleteError(int code,const void* data) = 0;
    };

    /**
    * 更新对象回调接口
    */
    class BmobUpdateDelegate{
    public:
    	/**
    	* 更新数据成功回调方法
    	* @param data 返回的数据
    	*/
    	virtual void onUpdateSucess(const void* data) = 0;
    	/**
    	* 更新失败回调方法
    	* @param code 返回的错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onUpdateError(int code,const void* data) = 0;
    };

    /**
    * 统计的回调接口
    */
    class BmobStaticsDelegate{
    public:
    	/**
    	* 统计成功的回调接口
    	* @param data 返回的数据
    	*/
    	virtual void onStaticsSucess(const void* data) = 0;
    	/**
    	* 统计错误的回调接口
    	* @param code 返回的错误码
    	* @param data 返回的错误数据
    	*/
    	virtual void onStaticsError(int code,const void* data) = 0;
    };

    /**
    * 查询数量回调接口
    */
    class BmobCountDelegate{
    public:
    	/**
    	* 查询成功回调
    	* @param data 返回的数据
    	*/
    	virtual void onCountSucess(const void* data) = 0;
    	/**
    	* 查询失败回调
    	* @param code 返回的错误码
    	* @param data 返回的错误信息
    	*/
    	virtual void onCountError(int code,const void* data) = 0;
    };

    /**
    * 云端代码操作回调接口
    */
    class BmobCloudDelegate{
    public:
        /**
        * 创建云端代码回调
        * @param code 创建云端代码返回状态码
        * @param data 创建云端代码返回数据
        * @return
        */
        virtual void onCreateCloud(int code,const void* data) = 0;
        /**
        * 执行远端代码回调
        * @param code   执行云端代码返回状态码
        * @param data   执行云端代码返回数据
        * @return
        */
        virtual void onExecCloud(int code,const void* data) = 0;
        /**
        * 删除云端代码回调
        * @param code 删除云端代码返回状态码
        * @param data 删除云端代码返回数据
        */
        virtual void onDeleteCloud(int code,const void *data) = 0;
        /**
        * 云端代码其他的错误
        * @param  code 错误状态码
        * @param data 错误的返回数据
        * @return void
        */
        virtual void onCloudError(int code,const void *data) = 0;
    };

    /**
    * sdk自定义查询回调函数
    */
    class BmobBQLDelegate{
    public:
        /**
        * 执行云端代码成功的回调函数
        * @param data   成功以后的返回数据
        */
        virtual void onBQLSuccess(const void* data) = 0;
        /**
        * 执行云端代码失败的回调函数
        * @param code   失败的返回代码
        * @param mas    失败的返回信息
        */
        virtual void onBQLFailure(const int code,const void* data) = 0;
    };

    /**
    * 上传设备信息回调接口
    */
    class BmobUpDeviceInfoDelegate{
    public:
        /**
        * 上传回调韩式
        * @param code 返回的状态码
        * @param data 返回的数据
        */
        virtual void onUpload(int code,const void *data) = 0;
    };
}

#endif
