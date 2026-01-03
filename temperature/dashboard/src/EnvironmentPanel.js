import { useEffect, useState } from "react";
import {
    LineChart,
    Line,
    XAxis,
    YAxis,
    Tooltip,
    Legend,
    ResponsiveContainer,
} from "recharts";

const API_URL = "/api/environment"; // using proxy
const REFRESH_INTERVAL = 20000;
const MAX_HISTORY = 20;

function EnvironmentPanel() {
    const [history, setHistory] = useState([]);
    const [error, setError] = useState(null);

    const fetchEnvironment = async () => {
        try {
            const response = await fetch(API_URL);
            if (!response.ok) throw new Error("Fetch failed");

            const data = await response.json();
            const now = new Date();

            const newEntry = {
                time: now.toLocaleTimeString(),
                temperature: data.temperature,
                humidity: data.humidity,
            };

            setHistory((prev) => {
                const updated = [...prev, newEntry];
                return updated.slice(-MAX_HISTORY);
            });

            setError(null);
        } catch (err) {
            setError("Unable to connect to sensor");
        }
    };

    useEffect(() => {
        fetchEnvironment();
        const interval = setInterval(fetchEnvironment, REFRESH_INTERVAL);
        return () => clearInterval(interval);
    }, []);

    return (
        <div style={styles.container}>
            <h2>🌍 Environment Dashboard</h2>

            {error && <div style={styles.error}>{error}</div>}

            {/* Current values */}
            <div style={styles.panel}>
                <div>🌡 <strong>{history.at(-1)?.temperature ?? "--"} °C</strong></div>
                <div>💧 <strong>{history.at(-1)?.humidity ?? "--"} %</strong></div>
            </div>

            {/* Chart */}
            <div style={styles.chart}>
                <ResponsiveContainer width="100%" height={250}>
                    <LineChart data={history}>
                        <XAxis dataKey="time" />
                        <YAxis />
                        <Tooltip />
                        <Legend />
                        <Line type="monotone" dataKey="temperature" strokeWidth={2} />
                        <Line type="monotone" dataKey="humidity" strokeWidth={2} />
                    </LineChart>
                </ResponsiveContainer>
            </div>

            {/* Table */}
            <table style={styles.table}>
                <thead>
                <tr>
                    <th>Time</th>
                    <th>Temperature (°C)</th>
                    <th>Humidity (%)</th>
                </tr>
                </thead>
                <tbody>
                {[...history].reverse().map((row, index) => (
                    <tr key={index}>
                        <td>{row.time}</td>
                        <td>{row.temperature}</td>
                        <td>{row.humidity}</td>
                    </tr>
                ))}
                </tbody>
            </table>
        </div>
    );
}

const styles = {
    container: {
        maxWidth: 800,
        margin: "auto",
        fontFamily: "Arial, sans-serif",
    },
    panel: {
        display: "flex",
        gap: 40,
        fontSize: 20,
        marginBottom: 20,
    },
    chart: {
        background: "#f5f7fa",
        padding: 20,
        borderRadius: 12,
        marginBottom: 20,
    },
    table: {
        width: "100%",
        borderCollapse: "collapse",
    },
    error: {
        color: "red",
        marginBottom: 10,
    },
};

export default EnvironmentPanel;
