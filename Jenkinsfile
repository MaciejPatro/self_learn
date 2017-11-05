pipeline {
    agent any
    stages {
        stage('Build UTs') { 
            steps {
		sh 'cmake -D CMAKE_CXX_COMPILER=clang++ .'
		sh 'make'
            }
        }
        stage('Running UTs') {
            steps {
                sh 'exercises/ut/exercisesTests -r junit > ut_results.xml'
            }
        }
    }
    post {
        always {
	    junit 'ut_results.xml'
	}
    }
}