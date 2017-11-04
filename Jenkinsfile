pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
                echo 'Building Unit Tests...'
		sh 'clang++ --version'
            }
        }
        stage('Running UTs') {
            steps {
                echo 'Running UTs'
                sh 'clang++ --version'
            }
        }
    }
}