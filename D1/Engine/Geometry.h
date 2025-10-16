#pragma once

template<typename T>
class Geometry
{
public:
	uint32 GetVertexCount() { return (uint32)m_vertices.size(); }
	void* GetVertexData() { return m_vertices.data(); }
	const Vector<T>& GetVertices() { return m_vertices; }

	uint32 GetIndexCount() { return static_cast<uint32>(m_indices.size()); }
	void* GetIndexData() { return m_indices.data(); }
	const Vector<uint32>& GetIndices() { return m_indices; }

	void AddVertex(const T& vertex) { m_vertices.push_back(vertex); }
	void AddVertices(const Vector<T>& vertices) { m_vertices.insert(m_vertices.end(), vertices.begin(), vertices.end()); }
	void SetVertices(const Vector<T>& vertices) { m_vertices = vertices; }

	void AddIndex(uint32 index) { m_indices.push_back(index); }
	void AddIndices(const Vector<uint32>& indices) { m_indices.insert(m_indices.end(), indices.begin(), indices.end()); }
	void SetIndices(const Vector<uint32>& indices) { m_indices = indices; }

private:
	Vector<T> m_vertices = {};
	Vector<uint32> m_indices = {};
};

