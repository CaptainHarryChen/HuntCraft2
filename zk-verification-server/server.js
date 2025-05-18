// server.js - 零知识证明验证服务器
const express = require('express');
const snarkjs = require('snarkjs');
const cors = require('cors');
const fs = require('fs');
const path = require('path');
const app = express();

// 启用JSON解析和CORS
app.use(express.json({limit: '10mb'}));
app.use(cors());

// 保存验证密钥的目录
const VK_PATH = path.join(__dirname, 'keys', 'verification_key.json');

// 确保keys目录存在
if (!fs.existsSync(path.join(__dirname, 'keys'))) {
    fs.mkdirSync(path.join(__dirname, 'keys'));
}

// 上传验证密钥的端点
app.post('/upload-key', (req, res) => {
    try {
        const { verificationKey } = req.body;

        if (!verificationKey) {
            return res.status(400).json({
                success: false,
                message: "缺少验证密钥数据"
            });
        }

        // 保存验证密钥
        fs.writeFileSync(VK_PATH, JSON.stringify(verificationKey, null, 2));

        res.json({
            success: true,
            message: "验证密钥上传成功"
        });
    } catch (error) {
        console.error('上传密钥错误:', error);
        res.status(500).json({
            success: false,
            message: "上传验证密钥时出错",
            error: error.message
        });
    }
});

// 验证证明的端点
app.post('/verify', async (req, res) => {
    try {
        const { proof, publicSignals } = req.body;

        if (!proof || !publicSignals) {
            return res.status(400).json({
                success: false,
                message: "缺少证明或公共输入数据"
            });
        }

        // 检查验证密钥是否存在
        if (!fs.existsSync(VK_PATH)) {
            return res.status(400).json({
                success: false,
                message: "验证密钥未上传，请先上传验证密钥"
            });
        }

        // 读取验证密钥
        const verificationKey = JSON.parse(fs.readFileSync(VK_PATH, 'utf8'));

        console.log("开始验证...");
        console.log("公共输入:", JSON.stringify(publicSignals).slice(0, 100) + "...");

        // 验证证明
        const isValid = await snarkjs.groth16.verify(verificationKey, publicSignals, proof);

        console.log("验证结果:", isValid);

        res.json({
            success: true,
            isValid,
            message: isValid ? "验证成功" : "验证失败"
        });
    } catch (error) {
        console.error('验证错误:', error);
        res.status(500).json({
            success: false,
            message: "验证服务错误",
            error: error.message
        });
    }
});

// 健康检查端点
app.get('/health', (req, res) => {
    res.json({ status: 'ok', message: '验证服务正常运行' });
});

const PORT = process.env.PORT || 3000;
app.listen(PORT, () => {
    console.log(`零知识证明验证服务运行在端口 ${PORT}`);
    console.log(`健康检查: http://localhost:${PORT}/health`);
});