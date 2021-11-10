-- Copyright (c) 2021 by yyyyshen

-- 使用lua做更灵活的配置

config = {

    zmq_ipc_addr = "tcp://127.0.0.1:5555",

    http_addr = "http://localhost/ljf_cpp_notes?token=cpp@2021",

    time_interval = 5,

    keyword = "super",

    sold_criteria = 100,

    revenue_criteria = 1000,

    best_n  = 3,

    max_buf_size = 4 * 1024,
}

-- more config
others = {
    -- add more
}

-- debug: luajit conf.lua

-- print(config.http_addr)