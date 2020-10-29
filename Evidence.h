#pragma once
#include <string>
#include <fstream>

class Evidence
{
private:
	std::string _id, _photograph;
	float _image_clarity_level;
	unsigned int _quantity, _measurement[3];
public:
	/// <summary>
	/// Creates an empty, invalid Evidence.
	/// </summary>
	Evidence();

	/// <summary>
	/// Copy constructor.
	/// </summary>
	/// <param name="EvidenceToCopy">Source of data.</param>
	Evidence(const Evidence& EvidenceToCopy);

	/// <summary>
	/// Parameterized constructor.
	/// </summary>
	/// <param name="ID">The ID of the Evidence.</param>
	/// <param name="Measurement">x, y, z measurement</param>
	/// <param name="ImageClarityLevel">Image clarity level, between 0 and 1 inclusively.</param>
	/// <param name="Quantity">Number of pieces of evidence.</param>
	Evidence(const std::string& ID, unsigned int Measurement[3], float ImageClarityLevel, unsigned int Quantity,
	         const std::string& Photograph);

	/// <summary>
	/// Checks if Evidence is valid.
	///	<para>In order to be valid, an Evidence instance must have:</para>
	/// <para>		- at least the measurement on x > 0;</para>
	/// <para>		- a Quantity > 0;</para>
	/// </summary>
	/// <returns>Whether the instance is a valid one.</returns>
	bool IsValid() const;

	/// <summary>
	/// Gets the ID of the Evidence.
	/// </summary>
	const std::string& ID() const;

	/// <summary>
	/// Gets the measurement of the Evidence as a string separated by 'X'
	/// </summary>
	std::string MeasurementString() const;

	/// <summary>
	/// Gets the X measurement.
	/// </summary>
	int MeasurementX() const;

	/// <summary>
	/// Gets the Y measurement.
	/// </summary>
	int MeasurementY() const;

	/// <summary>
	/// Gets the Z measurement.
	/// </summary>
	int MeasurementZ() const;

	/// <summary>
	/// Gets the ImageClarityLevel of the Evidence.
	/// </summary>
	float ImageClarityLevel() const;

	/// <summary>
	/// Gets the Quantity of Evidence.
	/// </summary>
	unsigned int Quantity() const;

	/// <summary>
	/// Gets the photograph name.
	/// </summary>
	const std::string& Photograph() const;

	/// <summary>
	/// Copies an Evidence instance.
	/// </summary>
	static void* CopyEvidence(void* evidence);

	/// <summary>
	/// Destroys an Evidence instance.
	/// </summary>
	static void DestroyEvidence(void* evidence);

	/// <summary>
	/// Converts std::string to Evidence.
	/// </summary>
	static Evidence* FromString(const std::string& String);

	/// <summary>
	/// Converts Evidence to std::string.
	/// </summary>
	friend std::string to_string(const Evidence& evidence);

	friend std::istream& operator>>(std::istream& in, Evidence& evidence);
	friend std::ostream& operator<<(std::ostream& out, const Evidence& evidence);
};
