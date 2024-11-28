import pandas as pd

input_file = 'datasets/spotify_charts_2014-22.csv'
output_file = 'output.csv'
#selecting the columns required
selected_columns_names = ['date', 'country', 'artist_genres', 'duration'] 
#defining the values for country
mapping_dict = {
    'country': {'ca': 0, 'global': 1, 'de': 2, 'jp': 3, 'in': 4, 'us': 5, 'mx': 6, 'uk': 7}
}

df = pd.read_csv(input_file) #reading the input file
selected_columns = df[selected_columns_names].copy()

# Filter rows based on the country values present in the mapping_dict
selected_columns = selected_columns[selected_columns['country'].isin(mapping_dict['country'].keys())]

# Convert the country values to their corresponding integer codes using mapping_dict
selected_columns['country'] = selected_columns['country'].map(mapping_dict['country'])

selected_columns['deadline'] = selected_columns['duration'] % 10000 #defining the deadline
#
selected_columns = selected_columns[['date', 'deadline', 'country', 'artist_genres']]

selected_columns.head(400000).to_csv(output_file, index=False)

print(f"Selected columns have been written to {output_file}.")